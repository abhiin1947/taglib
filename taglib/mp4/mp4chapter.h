/**************************************************************************
    copyright            : (C) 2013 by Abhinandan Ramaprasath
    email                : abhiin1947@gmail.com
 **************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_MP4CHAPTER_H
#define TAGLIB_MP4CHAPTER_H

#include "tlist.h"
#include "taglib_export.h"

namespace TagLib {

  namespace MP4 {

    class TAGLIB_EXPORT MP4Chapters
    {
    public:
      enum ChapterType 
      {
        QtChapterType,
        NeroChapterType
      };

      MP4Chapters(Taglib::MP4::File *file);
      /*
       * Gives a count of the chapters in the mp4 file
       */
      unsigned int getCount();

      /*
       * Returns the pointer to the array of MP4Chapter instances
       */
      MP4ChapterList getChapters();

      /*
       * return chapter type
       */
      ChapterType getChapterType();

    private:

      /*
       * The array of MP4Chapter classes
       */
      MP4ChapterList chapters;

      ChapterType type;

      unsigned int count;
    };
    class TAGLIB_EXPORT MP4Chapter
    {
    public:

      char* getTitle();

      unsigned long long getDuration();
    
    private:
      
      unsigned long long duration;
      
      unsigned long offset;
      
      char title[16];
    };
    typedef List<MP4Chapter> MP4ChapterList;
  }

}

#endif
