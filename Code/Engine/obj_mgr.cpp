//==============================================================================
//
//  obj_mgr.cpp
//
//==============================================================================
//  Copyright (C) DejaTools, LLC.  All rights reserved.
//==============================================================================

//==============================================================================
//  INCLUDES
//==============================================================================

#include "obj_mgr.h"
#include "engine.h"
#include <string.h> // strcmp()
#include "DejaLib.h"
#include "DejaPrivate.h"


//==============================================================================
//  STORAGE
//==============================================================================

obj_mgr ObjMgr;

type_data*  obj_mgr::m_TypeInfo[ MAX_TYPES ] = { 0 };
object*     obj_mgr::m_pObject[ MAX_OBJECTS ] = { 0 };
int         obj_mgr::m_nTypes = 0;
int         obj_mgr::m_nObjects = 0;

//==============================================================================
//  FUNCTIONS - type_data
//==============================================================================

type_data:: type_data( void )
{
    // 'void' construction is not allowed.
    ASSERT( false );
}

//==============================================================================

type_data:: type_data( const char* apTypeName , factory_fn* apFactoryFn )
:   m_Type( -1 ) ,
    m_pName( apTypeName ) ,
    m_pFactoryFn( apFactoryFn ) ,
    m_nInstances( 0 ) ,
    m_pFirst( NULL ) ,
    m_pCursor( NULL )
{

}

//==============================================================================

type_data:: ~type_data( void )
{
    // Do some sanity checks on the way out.
    if ( m_pName == NULL )
    {
        DEJA_WARNING( "type_data::~type_data" ,
                      "Type never named -- type_data at 0x%P" , this );
    }
    else
        if ( m_Type == -1 )
        {
            DEJA_WARNING( "type_data::~type_data" ,
                          "Type '%s' was never registered" , m_pName );
        }
}

//==============================================================================
//  FUNCTIONS - object
//==============================================================================

object::object( void )
:   m_Id( -1 ) ,
    m_pTypeData( NULL ) ,
    m_pNext( NULL ) ,
    m_pPrev( NULL )
{
}

//==============================================================================

object::~object( void )
{
    ASSERT( m_Id == -1 );
}

//==============================================================================

int object::GetID( void )
{
    return( m_Id );
}

//==============================================================================
//  FUNCTIONS - obj_mgr
//==============================================================================

obj_mgr::obj_mgr( void )
{
    // 'Singleton' construction sanity check.
    ASSERT( !m_Initialized );
    m_Initialized = true;
    m_NextSlot = 0;
}

//==============================================================================

obj_mgr::~obj_mgr( void )
{
    // 'Singleton' destruction sanity check.
    ASSERT( m_Initialized );
    m_Initialized = false;

    // ObjMgr sanity checks.
    ASSERT( m_nObjects == 0 );
}

//==============================================================================

int obj_mgr::RegisterType( type_data& TypeData )
{
    ASSERT( m_Initialized );
    ASSERT( m_nTypes < MAX_TYPES );
    ASSERT( TypeData.m_pName );

    // Search the registered types to see if this type is already listed.
    for ( int i = 0; i < m_nTypes; i++ )
    {
        if ( m_TypeInfo[ i ] == &TypeData )
        {
            return( i );
        }
    }

    // Type was not previously registered.  Do so now.
    int Result = m_nTypes;
    m_TypeInfo[ m_nTypes ] = ( type_data* ) &TypeData;
    TypeData.m_Type = m_nTypes;
    m_nTypes += 1;
    return( Result );
}

//==============================================================================

void obj_mgr::ResetTypeLoop( int iType )
{
    ASSERT( m_Initialized );
    ASSERT( iType < m_nTypes );

    m_TypeInfo[ iType ]->m_pCursor = m_TypeInfo[ iType ]->m_pFirst;
}

//==============================================================================

object* obj_mgr::GetNextInType( int iType )
{
    ASSERT( m_Initialized );
    ASSERT( iType < m_nTypes );

    object* pObject = m_TypeInfo[ iType ]->m_pCursor;

    if ( pObject )
    {
        m_TypeInfo[ iType ]->m_pCursor = pObject->m_pNext;
    }

    return( pObject );
}

//==============================================================================

object* obj_mgr::GetObjByID( int ID )
{
    if ( ID == -1 )
        return NULL;
    else
        return( m_pObject[ ID ] );
}

//==============================================================================

int obj_mgr::TypeNameToIndex( const char* pTypeName )
{
    ASSERT( pTypeName );

    for ( int iType = 0; iType < MAX_TYPES; iType++ )
    {
        if ( ( m_TypeInfo[ iType ] ) &&
            ( strcmp( pTypeName , m_TypeInfo[ iType ]->m_pName ) == 0 ) )
        {
            return iType;
        }
    }

    // Not found
    return -1;
}

//==============================================================================

object* obj_mgr::CreateObject( int iType )
{
    ASSERT( m_nObjects < MAX_OBJECTS );
    ASSERT( m_TypeInfo[ iType ] );

    object* pObject = m_TypeInfo[ iType ]->m_pFactoryFn( );
    pObject->m_pTypeData = m_TypeInfo[ iType ];
    m_TypeInfo[ iType ]->m_nInstances += 1;
    return( pObject );
}

//==============================================================================

object* obj_mgr::CreateObject( const char* pTypeName )
{
    int iType = TypeNameToIndex( pTypeName );
    if ( iType != -1 )
        return( CreateObject( iType ) );

    ASSERT( false );
    return( NULL );
}

//==============================================================================

void obj_mgr::AddObject( object* pObject )
{
    ASSERT( pObject );
    ASSERT( pObject->m_pTypeData );
    ASSERT( m_TypeInfo[ pObject->m_pTypeData->m_Type ] == pObject->m_pTypeData );

    // Search for an available slot.
    int Slot = m_NextSlot;
    for ( int i = 0; i < MAX_OBJECTS; i++ )
    {
        if ( !m_pObject[ Slot ] )
        {
            // Grab a reference to the type data for ease of access.
            type_data& TypeInfo = *( pObject->m_pTypeData );

            // Slot the object in.
            m_pObject[ Slot ] = pObject;
            pObject->m_Id = Slot;

            // Link the object into the type chain.
            object*& pFirst = TypeInfo.m_pFirst;
            pObject->m_pNext = pFirst;
            pObject->m_pPrev = NULL;
            if ( pFirst )
            {
                pFirst->m_pPrev = pObject;
            }
            pFirst = pObject;

            // Bump up the object count.
            m_nObjects += 1;

            // Update the next slot to allocate.
            m_NextSlot = ( Slot + 1 ) % MAX_OBJECTS;

            // And we're done.
            return;
        }
        else
        {
            Slot = ( Slot + 1 ) % MAX_OBJECTS;
        }
    }

    DEJA_ERROR( "obj_mgr::AddObject" , "ObjMgr is FULL." );
    ASSERT( false );
}

//==============================================================================

void obj_mgr::RemoveObject( object* pObject )
{
    ASSERT( pObject );
    ASSERT( m_pObject[ pObject->m_Id ] == pObject );

    // Inform the object.
    pObject->OnRemove( );

    // Grab a reference to the type data for ease of access.
    type_data& TypeInfo = *( pObject->m_pTypeData );

    // Slot the object out.
    m_pObject[ pObject->m_Id ] = NULL;
    pObject->m_Id = -1;

    // Unlink the object from the type chain.
    if ( TypeInfo.m_pFirst == pObject ) TypeInfo.m_pFirst = pObject->m_pNext;
    if ( pObject->m_pNext )  pObject->m_pNext->m_pPrev = pObject->m_pPrev;
    if ( pObject->m_pPrev )  pObject->m_pPrev->m_pNext = pObject->m_pNext;

    // If the type cursor is on the object, move it to the next.
    if ( TypeInfo.m_pCursor == pObject )
        TypeInfo.m_pCursor = pObject->m_pNext;

    // In the interest of safety, clear the object's type chain pointers.
    pObject->m_pNext = NULL;
    pObject->m_pPrev = NULL;

    // Bump down the object count.
    m_nObjects -= 1;
}

//==============================================================================

void obj_mgr::RemoveObject( int ID )
{
    ASSERT( m_pObject[ ID ] );
    RemoveObject( m_pObject[ ID ] );
}

//==============================================================================

void obj_mgr::DestroyObject( object* pObject )
{
    ASSERT( pObject );
    ASSERT( pObject->m_Id == -1 );
    ASSERT( pObject->m_pTypeData );

    pObject->m_pTypeData->m_nInstances -= 1;
    pObject->m_pTypeData = NULL;

    // Delete the object.
    delete pObject;
}

//==============================================================================

void obj_mgr::RemoveDestroy( int ID )
{
    ASSERT( m_pObject[ ID ] );

    object* pObject = m_pObject[ ID ];

    RemoveObject( pObject );
    DestroyObject( pObject );
}

//==============================================================================

void obj_mgr::RemoveDestroy( object* pObject )
{
    ASSERT( pObject );

    RemoveObject( pObject );
    DestroyObject( pObject );
}

//==============================================================================

void obj_mgr::RemoveDestroyAll( void )
{
    for ( int i = 0; i<MAX_OBJECTS; i++ )
    {
        object* pObject = m_pObject[ i ];
        if ( pObject )
        {
            RemoveDestroy( pObject );
            m_pObject[ i ] = NULL;
        }
    }
}

//==============================================================================

void obj_mgr::Update( float DeltaTime )
{
    DEJA_CONTEXT( "obj_mgr::Update" );
    for ( int i = 0; i < MAX_OBJECTS; i++ )
    {
        if ( m_pObject[ i ] )
        {
            m_pObject[ i ]->OnLogic( DeltaTime );
        }
    }
}

//==============================================================================

void obj_mgr::Render( void )
{
    DEJA_CONTEXT( "obj_mgr::Render" );
    for ( int i = 0; i < MAX_OBJECTS; i++ )
    {
        if ( m_pObject[ i ] )
        {
            m_pObject[ i ]->OnRender( );
        }
    }
}

//==============================================================================
