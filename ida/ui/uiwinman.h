/*
===========================================================================
Copyright (C) 2015 the OpenMoHAA team

This file is part of OpenMoHAA source code.

OpenMoHAA source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

OpenMoHAA source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenMoHAA source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

typedef struct Binding_s {
	str binding;
	int key1;
	int key2;
} Binding;

typedef struct UIWindowManager_s {
	UIWidget baseClass;
	unsigned int m_lastbuttons;
	UIPoint2D m_oldpos;
	SafePtr2_t m_oldview;
	SafePtr2_t m_firstResponder;
	UIWidget *m_activeControl;
	UIWidget *m_backgroundwidget;
	UIReggedMaterial *m_cursor;
	str m_cursorname;
	bool m_showcursor;
	Container_t m_materiallist;
	bool m_amidead;
	UIWidget *m_bindactive;
	Container_t bindings;
} UIWindowManager;
