
#include  <windows.h>
#include  "d:\apez\weblib\common\fieldef.h"

// ���]�w
void  DBFIELD_SET( FIELDEF *p, char *Ename, char Etype, int Elen, int Edec,
                   char *Cname, int Clen, int CtrlMode, int ModiMode, int FldSec  )
{
    strcpy( p->Ename, Ename );
    p->type         = Etype;
    p->width        = Elen;
    p->decimals     = Edec;
    strcpy( p->Cname, Cname );
    p->Cname_len    = Clen ;
    p->ctrl_mode    = CtrlMode ;
    p->modi_mode    = ModiMode ;
    p->fld_sec      = FldSec;
}

static  FIELDEF  *now_stru;
static  int       now_colN = 0;

void  DBFIELD_USE( FIELDEF *FieldStru, int FieldColN )
{
    now_stru = FieldStru;
    now_colN = FieldColN;
}

// ����W��X���s��
int  DBFIELD_WHERE( char *FieldName )
{
int ii;

    if( now_colN == 0 )
        return( -1 );
    for( ii=0; ii<now_colN; ii++ )
        if( !strcmp( now_stru[ii].Ename, FieldName ) )
            break;
    if( ii == now_colN )
        return( -1 );

return( ii );

}

// �M���w�İ�
void  DBFIELD_CLEAR( void )
{
int     ii;
FIELDEF *p;

    if( now_colN == 0 )
        return;
    p = now_stru;
    for( ii=1; ii<=now_colN; ii ++ )
    {
        p->value[0] = '\0';
        p ++;
    }
}

// �m�J�Y�� value ��
void  DBFIELD_REPL( char *FieldName, char *save_value )
{
int  ii;

    if( (ii=DBFIELD_WHERE(FieldName)) != -1 )
        strcpy( now_stru[ii].value, save_value );
}

// ���X�Y�� value ��
char  *DBFIELD_GFD( char *FieldName, char *ret_value )
{
int  ii;

    if( (ii=DBFIELD_WHERE(FieldName)) != -1 )
        strcpy( ret_value, now_stru[ii].value );

    return( ret_value );
}

// �����Ǧ^�Y�� value �ȫ���
char  *DBFIELD_GFV( char *FieldName )
{
int  ii;

    if( (ii=DBFIELD_WHERE(FieldName)) != -1 )
        return( now_stru[ii].value );

    return( NULL );
}
