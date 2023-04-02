import os
import sys
import yaml

def load_yaml(file_path):
    """Load a YAML file and return its contents as a Python object."""
    with open(file_path, 'r', encoding='utf-8', newline='') as f:
        return yaml.safe_load(f)


def resolve_refs(content, base_path, resolved_files):
    """Recursively resolve all $ref references in the YAML content."""
    if isinstance(content, dict):
        for k, v in content.items():
            if k == '$ref':
                ref_path = os.path.join(base_path, v)
                ref_path = os.path.abspath(ref_path)
                if ref_path not in resolved_files:
                    resolved_files[ref_path] = load_yaml(ref_path)
                    resolve_refs(resolved_files[ref_path], os.path.dirname(ref_path), resolved_files)
                content = resolved_files[ref_path]
            else:
                resolve_refs(v, base_path, resolved_files)
    elif isinstance(content, list):
        for item in content:
            resolve_refs(item, base_path, resolved_files)
    return content

def have_refs(yaml):
    if isinstance(yaml, dict):
        for k, v in yaml.items():
            if k == '$ref':
                return True
            elif have_refs(v):
                return True
    elif isinstance(yaml, list):
        for item in yaml:
            if have_refs(item):
                return True
    return False

def replace_ref(yaml, dir_path, ref_path, ref_src):
    if isinstance(yaml, dict):
        for k, v in yaml.items():
            if isinstance(v, dict):
                if len(v) == 1 and '$ref' in v.keys():
                    if isinstance(v['$ref'], str):
                        check_path = os.path.abspath(os.path.join(dir_path, v['$ref']))
                        if check_path == ref_path:
                            yaml[k] = ref_src
                else:
                    replace_ref(v, dir_path, ref_path, ref_src)
            elif isinstance(v, list):
                for count, item in enumerate(v):
                    if isinstance(item, dict) and len(item) == 1 and '$ref' in item.keys():
                        v[count] = ref_src
                    else:
                        replace_ref(v[count], dir_path, ref_path, ref_src)
    elif isinstance(yaml, list):
        for count, item in enumerate(yaml):
            if isinstance(item, dict) and len(item) == 1 and '$ref' in item.keys():
                yaml[count] = ref_src
            else:
                replace_ref(yaml[count], dir_path, ref_path, ref_src)



def create_final_content(refs):
    while len(refs) > 1:
        old_refs = refs.copy()
        for replacer_filepath, replacer_data in old_refs.items():
            if not have_refs(replacer_data):
                for filepath, data in refs.items():
                    replace_ref(data, os.path.dirname(filepath), replacer_filepath, replacer_data)
                if len(refs) > 1:
                    refs.pop(replacer_filepath)
    return list(refs.values())[0]

def main():
    if len(sys.argv) < 3:
        print('Usage: python3 merge_yaml.py <input_file> <output_file>')
        return
    
    input_path = sys.argv[1]
    output_path = sys.argv[2]
    input_path = os.path.abspath(input_path)
    # Step 1: Collect all files
    refs = {}
    refs[input_path] = load_yaml(input_path)
    resolve_refs(refs[input_path], os.path.dirname(input_path), refs)

    # Step 3: Create final_content
    yaml.Dumper.ignore_aliases = lambda *args: True
    final_content = create_final_content(refs)
    with open(output_path, 'w', encoding='utf-8') as result_f:
        yaml.dump(final_content, result_f, allow_unicode=True)


if __name__ == '__main__':
    main()
