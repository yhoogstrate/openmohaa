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

// actor_anim.cpp

#include "actor.h"

void Actor::InitAnim
	(
	GlobalFuncs_t *func
	)

{
	func->ThinkState					= &Actor::Think_Anim;
	func->BeginState					= &Actor::Begin_Anim;
	func->PassesTransitionConditions	= &Actor::PassesTransitionConditions_Idle;
	func->FinishedAnimation				= &Actor::FinishedAnimation_Anim;
	func->ShowInfo						= &Actor::ShowInfo_Anim;
	func->IsState						= &Actor::IsIdleState;
}

void Actor::Begin_Anim
	(
	void
	)

{
	// FIXME: stub
	STUB();
}

void Actor::Think_Anim
	(
	void
	)

{
	// FIXME: stub
	STUB();
}

void Actor::FinishedAnimation_Anim
	(
	void
	)

{
	// FIXME: stub
	STUB();
}

void Actor::ShowInfo_Anim
	(
	void
	)

{
	// FIXME: stub
	STUB();
}
