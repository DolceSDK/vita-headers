#!/usr/bin/env python3

import pathlib
import sys

symbol_start = ('        functions:', '        variables:')

def symbol_name(a):
	return a.strip().split(':')[0]

yml_lines = pathlib.Path(sys.argv[1]).read_text(encoding='utf-8').splitlines()

while yml_lines != []:
	line = yml_lines.pop(0)
	if line in symbol_start:
		symbols = []
		while yml_lines != [] and yml_lines[0].startswith(' ' * 10) and not yml_lines[0].strip().startswith('#'):
			symbols.append(yml_lines.pop(0))
		sorted_symbols = list(sorted(symbols, key=symbol_name))
		for s, ss in zip(symbols, sorted_symbols):
			s = symbol_name(s)
			ss = symbol_name(ss)
			if s != ss:
				print(f'Disorder: found {s} but expected {ss}')
				print('Correct ordering:')
				for s in sorted_symbols:
					print(s)
				sys.exit(1)
