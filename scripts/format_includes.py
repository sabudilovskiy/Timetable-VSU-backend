import sys

def check_line(line, words):
    for word in words:
        if line.startswith("#include \"" + word):
            return True
    return False


def format_line(line: str):
    return line.replace("\"", "<", 1).replace("\"", ">", 1)



def format_file(input_path, words):
    with open(input_path, 'r') as file:
        content = file.readlines()

    formatted_content = []
    for line in content:
        if check_line(line, words):
            formatted_content.append(format_line(line))
        else:
            formatted_content.append(line)

    with open(input_path, 'w') as file:
        file.writelines(formatted_content)


def main():
    if len(sys.argv) < 3:
        print('Usage: python3 format_includes.py <input_file> start_words...')
        return

    input_path = sys.argv[1]
    words = sys.argv[2:]
    format_file(input_path, words)


if __name__ == '__main__':
    main()
