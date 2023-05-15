CMAKE_COMMON_FLAGS ?= -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
CMAKE_DEBUG_FLAGS ?= -DUSERVER_SANITIZE='addr ub'
CMAKE_RELEASE_FLAGS ?=
CMAKE_OS_FLAGS ?= -DUSERVER_FEATURE_CRYPTOPP_BLAKE2=0 -DUSERVER_FEATURE_REDIS_HI_MALLOC=1
NPROCS ?= $(shell nproc)
CLANG_FORMAT ?= clang-format-11

# NOTE: use Makefile.local for customization
-include Makefile.local

.PHONY: all
all: test-debug test-release

# Debug cmake configuration
build_debug/Makefile:
	@git submodule update --init
	@mkdir -p build_debug
	@cd build_debug && \
      cmake -DCMAKE_BUILD_TYPE=Debug $(CMAKE_COMMON_FLAGS) $(CMAKE_DEBUG_FLAGS) $(CMAKE_OS_FLAGS) $(CMAKE_OPTIONS) ..

# Release cmake configuration
build_release/Makefile:
	@git submodule update --init
	@mkdir -p build_release
	@cd build_release && \
      cmake -DCMAKE_BUILD_TYPE=Release $(CMAKE_COMMON_FLAGS) $(CMAKE_RELEASE_FLAGS) $(CMAKE_OS_FLAGS) $(CMAKE_OPTIONS) ..

# Run cmake
.PHONY: cmake-debug cmake-release
cmake-debug cmake-release: cmake-%: build_%/Makefile

# Build using cmake
.PHONY: build-debug build-release
build-debug build-release: build-%: cmake-%
	@cmake --build build_$* -j $(NPROCS) --target timetable_vsu_backend

# Test All
.PHONY: test-debug test-release
test-debug test-release: test-%: build-%
	@rm -rf tests/results
	@cmake --build build_$* -j $(NPROCS) --target timetable_vsu_backend_unittest
	@cmake --build build_$* -j $(NPROCS) --target timetable_vsu_backend_benchmark
	@cd build_$* && ((test -t 1 && GTEST_COLOR=1 PYTEST_ADDOPTS="--color=yes" ctest -V) || ctest -V)
	@pep8 tests

#run only testsuite tests
#use make testsuite-debug F="some regex" if you want filter tests by regex
.PHONY: testsuite-debug testsuite-release
testsuite-debug testsuite-release: testsuite-%: build-%
	@rm -rf tests/results
	@cd build_$* && ((test -t 1 && GTEST_COLOR=1 PYTEST_ADDOPTS="--color=yes $(if $(F),-k $(F))" ctest -V -R "testsuite"))

# Start the service (via testsuite service runner)
.PHONY: service-start-debug service-start-release
service-start-debug service-start-release: service-start-%: build-%
	@cd ./build_$* && $(MAKE) start-timetable_vsu_backend

.PHONY: add-eol
add-eol:
	@find $(P) -type f | while read file; do \
        if ! tail -c1 "$$file" | grep -q "^$$"; then \
            # echo "Adding EOL to $$file"; \
            echo >> "$$file"; \
        fi \
    done

# Cleanup data
.PHONY: clean-debug clean-release
clean-debug clean-release: clean-%:
	cd build_$* && $(MAKE) clean

.PHONY: check-pep8
check-pep8:
	@pep8 tests

.PHONY: dist-clean
dist-clean:
	@rm -rf build_*
	@rm -f ./configs/static_config.yaml
	@rm -rf tests/__pycache__/
	@rm -rf tests/.pytest_cache/

# Install
.PHONY: install-debug install-release
install-debug install-release: install-%: build-%
	@cd build_$* && \
		cmake --install . -v --component timetable_vsu_backend
	mv /usr/local/bin/timetable_vsu_backend /usr/local/bin/timetable_vsu_backend_$*

.PHONY: nothing-debug nothing-release
nothing-debug nothing-release:

.PHONY: run-debug run-release
run-debug run-release: run-%: nothing-%
	@/usr/local/bin/timetable_vsu_backend_$* --config /usr/local/etc/timetable_vsu_backend/static_config.yaml

.PHONY: install-run-debug install-run-release
install-run-debug install-run-release: install-run-%: install-%
	$(MAKE) run-$*

.PHONY: format-cpp
format-cpp:
	@find benchs -name '*pp' -type f | xargs $(CLANG_FORMAT) -i
	@find service -name '*pp' -type f | xargs $(CLANG_FORMAT) -i
	@find src -name '*pp' -type f | xargs $(CLANG_FORMAT) -i
	@find utests -name '*pp' -type f | xargs $(CLANG_FORMAT) -i
	$(MAKE) add-eol P=benchs
	$(MAKE) add-eol P=service
	$(MAKE) add-eol P=src
	$(MAKE) add-eol P=utests

# Format the sources
.PHONY: format-all
format-all: format-cpp
	@find tests -name '*.py' -type f | xargs autopep8 -i
	$(MAKE) add-eol P=api
	$(MAKE) add-eol P=tests
	$(MAKE) add-eol P=scripts
	$(MAKE) add-eol P=postgresql
	$(MAKE) add-eol P=configs_testing
	$(MAKE) add-eol P=configs
	$(MAKE) add-eol P=CMakeLists.txt
	$(MAKE) add-eol P=redocly.yaml
	$(MAKE) add-eol P=united_api.yaml

# Check format the sources
.PHONY: check-format
check-format: check-format-cpp
	$(MAKE) check-pep8

.PHONY: check-git-status
check-git-status:
	@echo "Checking if all files are committed to git..."
	@if [ -n "$$(git status --porcelain)" ]; then \
		echo "The following files are not committed:"; \
		git status --short; \
		echo "Please commit all changes and try again."; \
		git diff --color | cat; \
		exit 1; \
	else \
		echo "All files are committed to git."; \
	fi

.PHONY: check-format-cpp
check-format-cpp:
	@$(CLANG_FORMAT) --version
	@find benchs -name '*pp' -type f | xargs $(CLANG_FORMAT) -i --dry-run --Werror
	@find service -name '*pp' -type f | xargs $(CLANG_FORMAT) -i --dry-run --Werror
	@find src -name '*pp' -type f | xargs $(CLANG_FORMAT) -i --dry-run --Werror
	@find utests -name '*pp' -type f | xargs $(CLANG_FORMAT) -i --dry-run --Werror
.PHONY: gen
gen:
	@rm -rf .gen
	@mkdir -p .gen

	@find benchs -name '*pp' > .gen/benchs.txt
	@LC_COLLATE=C sort .gen/benchs.txt -r -o .gen/benchs.txt

	@find src -name '*pp' > .gen/objs.txt
	@LC_COLLATE=C sort .gen/objs.txt -r -o .gen/objs.txt

	@find service -name '*pp' > .gen/service.txt
	@LC_COLLATE=C sort .gen/service.txt -r -o .gen/service.txt

	@find utests -name '*pp' > .gen/unittest.txt
	@LC_COLLATE=C sort .gen/unittest.txt -r -o .gen/unittest.txt
	$(MAKE) add-eol P=.gen

.PHONY: unite-api
unite-api:
	@python3 scripts/merge_yaml.py api/api.yaml united_api.yaml

# # Internal hidden targets that are used only in docker environment
# --in-docker-start-debug --in-docker-start-release: --in-docker-start-%: install-%
# 	@sed -i 's/config_vars.yaml/config_vars.docker.yaml/g' /home/user/.local/etc/timetable_vsu_backend/static_config.yaml
# 	@psql 'postgresql://user:password@service-postgres:5432/timetable_vsu_backend_db-1' -f ./postgresql/data/initial_data.sql
# 	@/home/user/.local/bin/timetable_vsu_backend \
# 		--config /home/user/.local/etc/timetable_vsu_backend/static_config.yaml

# # Build and run service in docker environment
# .PHONY: docker-start-service-debug docker-start-service-release
# docker-start-service-debug docker-start-service-release: docker-start-service-%:
# 	@docker-compose run -p 8080:8080 --rm timetable_vsu_backend-container $(MAKE) -- --in-docker-start-$*

# # Start targets makefile in docker environment
# .PHONY: docker-cmake-debug docker-build-debug docker-test-debug docker-clean-debug docker-install-debug docker-cmake-release docker-build-release docker-test-release docker-clean-release docker-install-release
# docker-cmake-debug docker-build-debug docker-test-debug docker-clean-debug docker-install-debug docker-cmake-release docker-build-release docker-test-release docker-clean-release docker-install-release: docker-%:
# 	docker-compose run --rm timetable_vsu_backend-container $(MAKE) $*

# # Stop docker container and remove PG data
# .PHONY: docker-clean-data
# docker-clean-data:
# 	@docker-compose down -v
# 	@rm -rf ./.pgdata
