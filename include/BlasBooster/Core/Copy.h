#pragma once

#include "Cursor.h"
#include "Matrix.h"

namespace BlasBooster {

// TODO: Do not use cthe cursor if not needed

template <class T1, class P1, class T2, class P2>
void copy(Matrix<Dense,T1,P1> const& source, Matrix<Dense,T2,P2>& dest)
{
    typedef Cursor<const Matrix<Dense,T1,P1>, Direction::Row> SourceRowCursor;
    typedef Cursor<SourceRowCursor, Direction::Column> SourceColumnCursor;
    typedef Cursor<Matrix<Dense,T2,P2>, Direction::Row> DestRowCursor;
    typedef Cursor<DestRowCursor, Direction::Column> DestColumnCursor;

    SourceRowCursor sourceRowCur(source,0), sourceRowEnd(source,source.getNbRows());
    DestRowCursor destRowCur(dest,0);
    for ( ; sourceRowCur != sourceRowEnd; ++sourceRowCur, ++destRowCur )
    {
        SourceColumnCursor sourceColumnCur(source,sourceRowCur.begin()), sourceColumnEnd(source,sourceRowCur.end());
        DestColumnCursor destColumnCur(dest,destRowCur.begin());
        for ( ; sourceColumnCur != sourceColumnEnd; ++sourceColumnCur, ++destColumnCur )
        {
            *destColumnCur = *sourceColumnCur;
        }
    }
}

} // namespace BlasBooster
