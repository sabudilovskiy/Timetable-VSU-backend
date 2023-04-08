# timetable_vsu_backend

This C++ service use [userver framework](https://github.com/userver-framework/userver).


## Download and Build

Steps to use this service:
1. Clone the service 
2. Initialize submodules: `cd timetable_vsu_backend && git submodule update --init`
3. Use one of make commands

## Makefile

Makefile contains typicaly useful targets for development:

* `make build-debug` - debug build of the service with all the assertions and sanitizers enabled
* `make build-release` - release build of the service with LTO
* `make test-debug` - does a `make build-debug` and runs all the tests on the result
* `make test-release` - does a `make build-release` and runs all the tests on the result
* `make service-start-debug` - builds the service in debug mode and starts it
* `make service-start-release` - builds the service in release mode and starts it
* `make` or `make all` - builds and runs all the tests in release and debug modes
* `make format-all` - autoformat all the C++ and Python sources
* `make format-cpp` - autoformat all the C++ sources
* `make clean-` - cleans the object files
* `make dist-clean` - clean all, including the CMake cached configurations
* `make install` - does a `make build-release` and run install in directory set in environment `PREFIX`
* `make install-debug` - does a `make build-debug` and runs install in directory set in environment `PREFIX`
* `make docker-COMMAND` - run `make COMMAND` in docker environment
* `make docker-build-debug` - debug build of the service with all the assertions and sanitizers enabled in docker environment
* `make docker-test-debug` - does a `make build-debug` and runs all the tests on the result in docker environment
* `make docker-start-service-release` - does a `make install-release` and runs service in docker environment
* `make docker-start-service-debug` - does a `make install-debug` and runs service in docker environment
* `make docker-clean-data` - stop docker containers
* `make gen` - regenerate source lists for CMake in .gen
* `make check-format-cpp` - сheck formatting in C++ sources, if something is not formatted, an error will be returned
* `make check-format-all` - сheck formatting in all sources, if something is not formatted, an error will be returned
* `make unite-api` - create united api file(merged_api.yaml)
* `make check-git-status` - сheck if there are changes in files 

Edit `Makefile.local` to change the default configuration and build options.

## Known issues

### Clangd doesn't working with project
Use `ln -s build_debug/compile_commands.json compile_commands.json`

## License

The original template is distributed under the [Apache-2.0 License](https://github.com/userver-framework/userver/blob/develop/LICENSE)
and [CLA](https://github.com/userver-framework/userver/blob/develop/CONTRIBUTING.md).