from typing import List, Tuple, Set
import re

_include_re = re.compile(r'^\s*#include\s*'
                         r'[<"]'
                         r'([\w\-_/]+)'
                         r'[>"]'
                         r'\s*$')


def parse_source_file(filepath: str, libs: Set[str]) -> Tuple[List[str], str]:
    with open(filepath, 'r', encoding='UTF8') as fin:
        imports, contents = [], []
        for line in fin.readlines():
            mr = _include_re.match(line)
            if not mr:
                contents.append(line)
                continue

            g = mr.group(1)
            if g not in libs:
                contents.append(line)
                continue

            imports.append(g)
        return imports, ''.join(contents)


if __name__ == '__main__':
    print(parse_source_file('libs/graph/scc'))
