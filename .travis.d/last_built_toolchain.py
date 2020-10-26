#!/usr/bin/env python3

# DolceSDK Vita Headers
# Copyright (C) 2020 浅倉麗子
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# This file is for backward compatibility with older ddpm

import json
import urllib.request as request

RELEASES_URL = 'https://api.github.com/repos/DolceSDK/autobuilds/releases'

def last_built_toolchain(os='linux'):
	with request.urlopen(RELEASES_URL) as res:
		releases = json.loads(res.read().decode('utf-8'))
		for release in releases:
			for asset in release['assets']:
				if os in asset['name']:
					return asset['browser_download_url']
	raise Exception('Toolchain for OS not found')

if __name__ == '__main__':
	import sys

	try:
		url = last_built_toolchain(*sys.argv[1:])
	except Exception as e:
		print(e)
		sys.exit(1)

	print(url)
