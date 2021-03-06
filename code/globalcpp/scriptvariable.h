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

// scriptvariable.h: Dynamic variables for scripts.

#ifndef __SCRIPTVARIABLE_H__
#define __SCRIPTVARIABLE_H__

#include "listener.h"

#ifdef GAME_DLL
#include "misc.h"
#endif

enum variabletype
{
	VARIABLE_NONE,
	VARIABLE_STRING,
	VARIABLE_INTEGER,
	VARIABLE_FLOAT,
	VARIABLE_CHAR,
	VARIABLE_CONSTSTRING,
	VARIABLE_LISTENER,
	VARIABLE_REF,
	VARIABLE_ARRAY,
	VARIABLE_CONSTARRAY,
	VARIABLE_CONTAINER,
	VARIABLE_SAFECONTAINER,
	VARIABLE_POINTER,
	VARIABLE_VECTOR,
	VARIABLE_MAX
};

static const char *typenames[] =
{
	"none",
	"string",
	"int",
	"float",
	"char",
	"const string",
	"listener",
	"ref",
	"array",
	"const array",
	"array",
	"array",
	"pointer",
	"vector",
	"double"
};

class ScriptArrayHolder {
public:
	con_map< ScriptVariable, ScriptVariable > arrayValue;
	unsigned int	refCount;

public:
	void			Archive( Archiver& arc );
	static void		Archive( Archiver& arc, ScriptArrayHolder *& arrayValue );
};

class ScriptConstArrayHolder {
public:
	ScriptVariable			*constArrayValue;
	unsigned int			refCount;
	unsigned int			size;

public:
	void			Archive( Archiver& arc );
	static void		Archive( Archiver& arc, ScriptConstArrayHolder *& constArrayValue );

	ScriptConstArrayHolder( ScriptVariable *pVar, unsigned int size );
	ScriptConstArrayHolder( unsigned int size );
	ScriptConstArrayHolder();
	~ScriptConstArrayHolder();
};

class ScriptPointer {
public:
	Container< ScriptVariable * > list;

public:
	void			Archive( Archiver& arc );
	static void		Archive( Archiver& arc, ScriptPointer *& pointerValue );

	void		Clear();

	void		add( ScriptVariable *var );
	void		remove( ScriptVariable *var );
	void		setValue( const ScriptVariable& var );
};

class ScriptVariable {
public:
	short3			key;		// variable name
	unsigned char	type;		// variable type
	union anon393 {
	public:
		char						charValue;
		float						floatValue;
		int							intValue;
		SafePtr<Listener>			*listenerValue;
		str							*stringValue;
		float						*vectorValue;

		ScriptVariable				*refValue;

		ScriptArrayHolder			*arrayValue;
		ScriptConstArrayHolder		*constArrayValue;

		Container< SafePtr< Listener > >					*containerValue;
		SafePtr< ContainerClass< SafePtr< Listener > > >	*safeContainerValue;

		ScriptPointer								*pointerValue;
	} m_data;

private:
	void					ClearInternal();
	void					ClearPointerInternal();

public:
	CLASS_PROTOTYPE( ScriptVariable );

	ScriptVariable();
	ScriptVariable( const ScriptVariable& variable );

	~ScriptVariable();

	void					Archive( Archiver& arc );
	static void				Archive( Archiver& arc, ScriptVariable **obj );
	void					ArchiveInternal( Archiver& arc );

	void					CastBoolean( void );
	void					CastConstArrayValue( void );
	void					CastEntity( void );
	void					CastFloat( void );
	void					CastInteger( void );
	void					CastString( void );

	void					Clear();
	void					ClearPointer();

	const char				*GetTypeName( void ) const;
	variabletype			GetType( void ) const;

	qboolean				IsEntity( void );
	qboolean				IsListener( void );
	qboolean				IsNumeric( void );
#ifndef NO_SCRIPTENGINE
	qboolean				IsSimpleEntity( void );
#endif
	qboolean				IsString( void );
	qboolean				IsVector( void );

	void					PrintValue( void );

	void					SetFalse( void );
	void					SetTrue( void );

	int						arraysize( void ) const;
	size_t					size( void ) const;

	bool					booleanNumericValue( void );
	bool					booleanValue( void ) const;

#ifndef NO_SCRIPTENGINE
	str&					getName( void );

	short3&					GetKey();
	void					SetKey( const short3& key );
#endif

	Entity					*entityValue( void );

	void					evalArrayAt( ScriptVariable &var );

	void					setArrayAt( ScriptVariable &index, ScriptVariable &value );
	void					setArrayAtRef( ScriptVariable &index, ScriptVariable &value );
	void					setArrayRefValue( ScriptVariable &var );

	char					charValue( void ) const;
	void					setCharValue( char newvalue );

	ScriptVariable			*constArrayValue( void );
	void					setConstArrayValue( ScriptVariable *pVar, unsigned int size );

#ifndef NO_SCRIPTENGINE
	int						constStringValue( void ) const;
	void					setConstStringValue( const_str s );
#endif

	void					setContainerValue( Container< SafePtr< Listener > > *newvalue );
	void					setSafeContainerValue( ContainerClass< SafePtr< Listener > > *newvalue );

	float					floatValue( void ) const;
	void					setFloatValue( float newvalue );

	int						intValue( void ) const;
	void					setIntValue( int newvalue );

	Listener				*listenerValue( void ) const;
	void					setListenerValue( Listener * newvalue );

	void					newPointer( void );
	void					setPointer( const ScriptVariable& newvalue );

	void					setRefValue( ScriptVariable * ref );

	//const char				*stringValue( void );
	str						stringValue( void ) const;
	void					setStringValue( str newvalue );

#ifndef NO_SCRIPTENGINE
	SimpleEntity			*simpleEntityValue( void ) const;
#endif

	Vector					vectorValue( void ) const;
	void					setVectorValue( const Vector &newvector );

	class PathNode			*pathNodeValue( void ) const;
	class Waypoint			*waypointValue( void ) const;

	void					greaterthan( ScriptVariable &variable );
	void					greaterthanorequal( ScriptVariable &variable );
	void					lessthan( ScriptVariable &variable );
	void					lessthanorequal( ScriptVariable &variable );

	void					complement( void );
	void					minus( void );
	bool					operator=( const ScriptVariable& variable );
	ScriptVariable			&operator[]( ScriptVariable& index );
	ScriptVariable			*operator[]( unsigned index ) const;
	ScriptVariable			*operator*( );
	void					operator+=( const ScriptVariable& value );
	void					operator-=( const ScriptVariable& value );
	void					operator*=( const ScriptVariable& value );
	void					operator/=( const ScriptVariable& value );
	void					operator%=( const ScriptVariable& value );
	void					operator&=( const ScriptVariable& value );
	void					operator^=( const ScriptVariable& value );
	void					operator|=( const ScriptVariable& value );
	void					operator<<=( const ScriptVariable& value );
	void					operator>>=( const ScriptVariable& value );

	bool					operator!=( const ScriptVariable& value );
	bool					operator==( const ScriptVariable& value );

	ScriptVariable			operator++( int );
	ScriptVariable			operator--( int );
};

#ifndef NO_SCRIPTENGINE

class ScriptVariableList : public Class
{
private:
	con_set< short3, ScriptVariable > list;

public:
	CLASS_PROTOTYPE( ScriptVariableList );

	ScriptVariableList();

	virtual void	Archive( Archiver &arc );

	void			ClearList( void );

	ScriptVariable *GetOrCreateVariable( str name );
	ScriptVariable *GetOrCreateVariable( unsigned int name );

	ScriptVariable *GetVariable( str name );
	ScriptVariable *GetVariable( unsigned int name );

	ScriptVariable *SetVariable( const char *name, int value );
	ScriptVariable *SetVariable( const char *name, float value );
	ScriptVariable *SetVariable( const char *name, const char *value );
	ScriptVariable *SetVariable( const char *name, Entity *value );
	ScriptVariable *SetVariable( const char *name, Listener *value );
	ScriptVariable *SetVariable( const char *name, Vector &value );
	ScriptVariable *SetVariable( const char *name, ScriptVariable& value );
	ScriptVariable *SetVariable( unsigned int name, ScriptVariable& value );
};

#endif

#endif /* __SCRIPTVARIABLE_H__ */
