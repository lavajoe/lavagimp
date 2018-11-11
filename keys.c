/*
    lavagimp, autotype random quotes (gimps) by pressing hotkeys
	
    Copyright (C) 2018  lavajoe <joe89gunnar@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "lavagimp.h"

UINT findKey(char key[64]) {
	
	UINT modekey = 69696969;

	if (strcmp("home", key) == 0) {
	  modekey = 0x24;
	}
	if (strcmp("delete", key) == 0) {
	  modekey = 0x2E;
	}
	if (strcmp("insert", key) == 0) {
	  modekey = 0x2D;
	}
	if (strcmp("page_up", key) == 0) {
	  modekey = 0x21;
	}
	if (strcmp("page_down", key) == 0) {
	  modekey = 0x22;
	}
	if (strcmp("end", key) == 0) {
	  modekey = 0x23;
	}
	if (modekey == 69696969) {
		return 69696969;
	}

	return modekey;
}

