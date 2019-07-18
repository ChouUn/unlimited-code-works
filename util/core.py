import os
from typing import List, Dict, Tuple
import pyperclip

import networkx as nx

from util.parser import parse_source_file

SRC_DIR = 'src'
LIB_DIR = 'libs'


def travel(path: str, prefix: str = '') -> List[str]:
    res = []
    for entry in os.scandir(path):
        sub_path = f'{prefix}/{entry.name}'
        if entry.is_dir():
            sub_res = travel(entry.path, sub_path)
            res.extend(sub_res)
        else:
            res.append(sub_path)
    return res


def get_libs() -> List[str]:
    res = []
    for filepath in travel(LIB_DIR):
        filepath = filepath[1:]  # remove leading '/'
        res.append(filepath)
    return res


libs = set(get_libs())
# print('libs:', libs)

main_filepath = next((filepath for filepath in travel(SRC_DIR) if filepath.endswith('.cpp')))
main_filepath = f'{SRC_DIR}{main_filepath}'
# print('path of main file:', main_filepath)

mapping: Dict[str, Tuple[List[str], str]] = {}
queue: List[str] = [main_filepath]
while queue:
    head, queue = queue[0], queue[1:]
    if head in mapping: continue

    source_file = f'{LIB_DIR}/{head}' if head in libs else head
    mapping[head] = parse_source_file(source_file, libs)
    for lib in mapping[head][0]:
        queue.append(lib)

G = nx.DiGraph()
for key, value in mapping.items():
    for to in value[0]:
        G.add_edge(key, to)
output = ['''
#define NDEBUG
''']
for key in reversed(list(nx.topological_sort(G))):
    output.append(mapping[key][1])
output = '\n'.join(output)
pyperclip.copy(output)
