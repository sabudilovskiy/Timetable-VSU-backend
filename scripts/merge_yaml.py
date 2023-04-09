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


def is_ref_to_schemas(v):
    return v.startswith('#/components/schemas')


def have_refs(yaml):
    if isinstance(yaml, dict):
        for k, v in yaml.items():
            if k == '$ref':
                return not is_ref_to_schemas(v)
            elif have_refs(v):
                return True
    elif isinstance(yaml, list):
        for item in yaml:
            if have_refs(item):
                return True
    return False


def get_ref_name(base_path, path_to_file):
    relative_path = os.path.relpath(path_to_file, base_path)
    relative_path = relative_path.replace("\\", "/")

    if relative_path.startswith("./"):
        relative_path = relative_path[2:]

    if relative_path.endswith("."):
        relative_path = relative_path[:-1]

    file_extension = os.path.splitext(relative_path)[-1]
    if file_extension:
        relative_path = relative_path[:-len(file_extension)]

    result = ""
    relative_path = relative_path.replace('-', '/')
    relative_path = relative_path.replace('_', '/')
    for word in relative_path.split('/'):
        temp = word[0].upper() + word[1:]
        result += temp

    return result

def get_ref_name_path(base_path, path_to_file):
    result = '#/components/schemas/' + get_ref_name(base_path, path_to_file)
    return result

def replace_ref(yaml, dir_path, ref_path, ref_name):
    if isinstance(yaml, dict):
        for k, v in yaml.items():
            if isinstance(v, dict):
                if len(v) == 1 and '$ref' in v.keys():
                    if isinstance(v['$ref'], str):
                        check_path = os.path.abspath(os.path.join(dir_path, v['$ref']))
                        if check_path == ref_path:
                            yaml[k] = {'$ref': ref_name}
                else:
                    replace_ref(v, dir_path, ref_path, ref_name)
            elif isinstance(v, list):
                for count, item in enumerate(v):
                    if isinstance(item, dict) and len(item) == 1 and '$ref' in item.keys():
                        check_path = os.path.abspath(os.path.join(dir_path, item['$ref']))
                        if check_path == ref_path:
                            v[count] = {'$ref': ref_name}
                    else:
                        replace_ref(v[count], dir_path, ref_path, ref_name)
    elif isinstance(yaml, list):
        for count, item in enumerate(yaml):
            if isinstance(item, dict) and len(item) == 1 and '$ref' in item.keys():
                yaml[count] = {'$ref': ref_name}
            else:
                replace_ref(yaml[count], dir_path, ref_path, ref_name)


def create_final_content(refs, base_path):
    components_schemas = {}
    while len(refs) > 1:
        old_refs = refs.copy()
        for replacer_filepath, replacer_data in old_refs.items():
            if not have_refs(replacer_data):
                ref_name_path = get_ref_name_path(base_path, replacer_filepath)
                ref_name = get_ref_name(base_path, replacer_filepath)
                for filepath, data in refs.items():
                    replace_ref(data, os.path.dirname(filepath), replacer_filepath, ref_name_path)
                if len(refs) > 1:
                    components_schemas[ref_name] = replacer_data
                    refs.pop(replacer_filepath)
    result = list(refs.values())[0]
    result.setdefault('components', {})
    result['components'].setdefault('schemas', components_schemas)
    return result

def remove_schema_prefix(s):
    prefix = "#/components/schemas/"
    if s.startswith(prefix):
        s = s[len(prefix):]
    return s

def fix_views(yaml):
    newyaml = yaml
    for k, v in yaml['paths'].items():
        if isinstance(v, dict):
            if len(v) == 1 and '$ref' in v.keys():
                name_schema = remove_schema_prefix(v['$ref'])
                newyaml['paths'][k] = yaml['components']['schemas'][name_schema]
                del newyaml['components']['schemas'][name_schema]
        else:
            newyaml[k] = v
    return newyaml

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
    final_content = create_final_content(refs, os.path.dirname(input_path))
    fixed = fix_views(final_content)
    with open(output_path, 'w', encoding='utf-8') as result_f:
        yaml.dump(fixed, result_f, allow_unicode=True)


if __name__ == '__main__':
    main()
