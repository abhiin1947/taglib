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

#include "mp4chapter.h"
#include "mp4atom.h"

using namespace TagLib;

MP4::MP4Chapters::MP4Chapters(MP4::File *file)
{
  long long i;
  TagLib::MP4::File audioFile(file_name);
  TagLib::List<long long> offsets;
  TagLib::MP4::Atoms *root_atoms = new TagLib::MP4::Atoms(&audioFile);
  if(root_atoms)
  {
    TagLib::MP4::Atom *f_moov = root_atoms->find("moov");
    if(f_moov)
    {
      TagLib::MP4::AtomList f_trak = f_moov->findall("trak");
      if(f_trak.size()!=0)
      {
        TagLib::MP4::Atom *chap_trak = f_trak[1];
        if(chap_trak)
        {
          TagLib::MP4::AtomList chunk_data = chap_trak->findall("stco",true);
          if(chunk_data.size() != 0)
          {
            TagLib::MP4::AtomList time_data = chap_trak->findall("stts",true);
            if(time_data.size() != 0)
            {
              TagLib::MP4::Atom *off_chunk = chunk_data[0];
              if(off_chunk)
              {
                TagLib::MP4::Atom *dura_data = time_data[0];
                if(dura_data)
                {
                  audioFile.seek(off_chunk->offset  12);
                  long long no_of_chapters = audioFile.readBlock(4).toLongLong();
                  printf("no of chapters is %lld\n",no_of_chapters);
                    for(i=0;i<no_of_chapters;i)
                  {
                    offsets.append(audioFile.readBlock(4).toLongLong());
                  }
                  TagLib::MP4::Properties *au_prop = new TagLib::MP4::Properties(&audioFile,root_atoms);
                  audioFile.seek(dura_data->offset  12);
                  long long no_of_durations = audioFile.readBlock(4).toLongLong();
                  for(i=0;i<no_of_durations;)
                  {
                    long long t_len;
                    t_len = audioFile.readBlock(4).toLongLong();
                    i=t_len;
                    long long j;
                    for(j=0;j<t_len;j)
                    {
                      durations->append((audioFile.readBlock(4).toLongLong()*1000)/au_prop->sampleRate());
                    }
                  }

                  for(i=0;i<no_of_chapters;i)
                  {
                    audioFile.seek((unsigned int)offsets[i]);
                    uint title_size = audioFile.readBlock(2).toUInt();
                    char *title_name = (char *)malloc(title_size);
                    for(uint j=0;j<title_size;j)
                    {
                      title_name[j]= (char)audioFile.readBlock(1).toUInt();
                    }
                    title_name[title_size]='\0';
                    //printf("%s :: %lld\n",title_name,durations[i]);
                    QString ttl(title_name);
                    titles->append(ttl);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

unsigned int MP4::MP4Chapters::getCount()
{
  return count;
}

MP4ChapterList MP4::MP4Chapters::getChapters()
{
  return chapters;
}

ChapterType MP4::MP4Chapters::getChapterType()
{
  return type;
}

char* MP4::MP4Chapter::getTitle()
{
  return title;
}

unsigned long long MP4::MP4Chapter::getDuration()
{
  return duration;
}