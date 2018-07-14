#pragma once
#include "vector2.h"
class obj_mgr;
class type_data;
//==============================================================================
//  DEFINES
//==============================================================================

#define MAX_TYPES         32
#define MAX_OBJECTS     4096
//==============================================================================

class object
{
private:
        int         m_Id;
        vector2     m_Position;
        type_data*  m_pTypeData;
        object*     m_pNext;
        object*     m_pPrev;
public:
                    object          ( );
virtual		        ~object         ( );
virtual     void     OnLogic        ( float )                { };
virtual     void     OnRender       ( )                      { };
virtual     void     OnRemove       ( )                      { };
virtual     void     OnDejaObjInit  ( )                      { };
            int      GetID          ( );
const	    vector2& GetPosition    ( );
            void	 SetPosition    ( const vector2& V );
friend	    class obj_mgr;
};

//==============================================================================

typedef object* factory_fn( void );                                             

//==============================================================================

class type_data
{
public:
        int         m_Type;
const   char*       m_pName;
        factory_fn* m_pFactoryFn;
        int         m_nInstances;
        object*     m_pFirst;       // First instance of given type.
        object*     m_pCursor;      // Cursor for type iteration
                    type_data(const char* pTypeName,
                             factory_fn*  apFactoryFunc);
                    ~type_data();
private:
                    type_data();

};

//==============================================================================

class obj_mgr
{
public:

                    obj_mgr( void );
                    ~obj_mgr( void );

        int         RegisterType( type_data&        TypeData );
        void        ResetTypeLoop( int               iType );
        object*     GetNextInType( int               iType );

        object*     GetObjByID( int               ID );
        int         TypeNameToIndex( const char*       pTypeName );

        object*     CreateObject( int               iType );
        object*     CreateObject( const char*       pTypeName );
        void        AddObject( object*           pObject );
        void        RemoveObject( int               ID );
        void        RemoveObject( object*           pObject );
        void        DestroyObject( object*           pObject );
        void        RemoveDestroy( int               ID );
        void        RemoveDestroy( object*           pObject );
        void        RemoveDestroyAll( void );
        int         GetClosest( object*           pObject ,
                       const char*       pTypeName );

        void        ApplyDamage( const vector2&    Position ,
                                 int               OwnerID ,
                                 int               Damage ,
                                 float             InnerRadius ,
                                 float             OuterRadius );

        void        Update( float             DeltaTime );
        void        Render( void );

protected:

        bool        m_Initialized;
        int         m_NextSlot;

static  type_data*  m_TypeInfo[ MAX_TYPES ];
static  object*     m_pObject[ MAX_OBJECTS ];
static  int         m_nTypes;
static  int         m_nObjects;
};

//==============================================================================
//  STORAGE
//==============================================================================

extern obj_mgr  ObjMgr;