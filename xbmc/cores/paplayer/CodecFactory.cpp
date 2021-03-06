/*
 *      Copyright (C) 2005-2012 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "system.h"
#include "CodecFactory.h"
#include "ModplugCodec.h"
#include "NSFCodec.h"
#ifdef HAS_SPC_CODEC
#include "SPCCodec.h"
#endif
#include "SIDCodec.h"
#include "VGMCodec.h"
#include "YMCodec.h"
#include "TimidityCodec.h"
#ifdef HAS_ASAP_CODEC
#include "ASAPCodec.h"
#endif
#include "URL.h"
#include "DVDPlayerCodec.h"

ICodec* CodecFactory::CreateCodec(const CStdString& strFileType)
{
  if (strFileType.Equals("mp3") || strFileType.Equals("mp2"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("pcm") || strFileType.Equals("l16"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("ape") || strFileType.Equals("mac"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("cdda"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("mpc") || strFileType.Equals("mp+") || strFileType.Equals("mpp"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("shn"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("mka"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("flac"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("wav"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("dts") || strFileType.Equals("ac3") ||
           strFileType.Equals("m4a") || strFileType.Equals("aac") ||
           strFileType.Equals("pvr"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("wv"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("669")  ||  strFileType.Equals("abc") ||
           strFileType.Equals("amf")  ||  strFileType.Equals("ams") ||
           strFileType.Equals("dbm")  ||  strFileType.Equals("dmf") ||
           strFileType.Equals("dsm")  ||  strFileType.Equals("far") ||
           strFileType.Equals("it")   ||  strFileType.Equals("j2b") ||
           strFileType.Equals("mdl")  ||  strFileType.Equals("med") ||
           strFileType.Equals("mod")  ||  strFileType.Equals("itgz")||
           strFileType.Equals("mt2")  ||  strFileType.Equals("mtm") ||
           strFileType.Equals("okt")  ||  strFileType.Equals("pat") ||
           strFileType.Equals("psm")  ||  strFileType.Equals("ptm") ||
           strFileType.Equals("s3m")  ||  strFileType.Equals("stm") ||
           strFileType.Equals("ult")  ||  strFileType.Equals("umx") ||
           strFileType.Equals("xm")   || strFileType.Equals("mdgz") ||
           strFileType.Equals("s3gz") || strFileType.Equals("xmgz"))
    return new ModplugCodec();
  else if (strFileType.Equals("nsf") || strFileType.Equals("nsfstream"))
    return new NSFCodec();
#ifdef HAS_SPC_CODEC
  else if (strFileType.Equals("spc"))
    return new SPCCodec();
#endif
  else if (strFileType.Equals("sid") || strFileType.Equals("sidstream"))
    return new SIDCodec();
  else if (VGMCodec::IsSupportedFormat(strFileType))
    return new VGMCodec();
  else if (strFileType.Equals("ym"))
    return new YMCodec();
  else if (strFileType.Equals("wma"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("aiff") || strFileType.Equals("aif"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("xwav"))
    return new DVDPlayerCodec();
  else if (TimidityCodec::IsSupportedFormat(strFileType))
    return new TimidityCodec();
#ifdef HAS_ASAP_CODEC
  else if (ASAPCodec::IsSupportedFormat(strFileType) || strFileType.Equals("asapstream"))
    return new ASAPCodec();
#endif
  else if (strFileType.Equals("tta"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("tak"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("opus"))
    return new DVDPlayerCodec();
  else if (strFileType.Equals("dff") || strFileType.Equals("dsf"))
    return new DVDPlayerCodec();

  return new DVDPlayerCodec();
}

ICodec* CodecFactory::CreateCodecDemux(const CStdString& strFile, const CStdString& strContent, unsigned int filecache)
{
  CURL urlFile(strFile);
  if( strContent.Equals("audio/mpeg")
  ||  strContent.Equals("audio/mpeg3")
  ||  strContent.Equals("audio/mp3") )
  {
    DVDPlayerCodec *dvdcodec = new DVDPlayerCodec();
    dvdcodec->SetContentType(strContent);
    return dvdcodec;
  }
  else if (strContent.Left(9).Equals("audio/l16"))
  {
    DVDPlayerCodec *pCodec = new DVDPlayerCodec;
    pCodec->SetContentType(strContent);
    return pCodec;
  }
  else if( strContent.Equals("audio/aac") || strContent.Equals("audio/aacp") ||
      strContent.Equals("audio/x-ms-wma") ||
      strContent.Equals("audio/x-ape") || strContent.Equals("audio/ape") ||
      strContent.Equals("application/ogg") || strContent.Equals("audio/ogg") )
  {
    DVDPlayerCodec *pCodec = new DVDPlayerCodec;
    pCodec->SetContentType(strContent);
    return pCodec;
  }
  else if (strContent.Equals("audio/x-xbmc-pcm"))
  {
    // audio/x-xbmc-pcm this is the used codec for AirTunes
    // (apples audio only streaming)
    DVDPlayerCodec *dvdcodec = new DVDPlayerCodec();
    dvdcodec->SetContentType(strContent);
    return dvdcodec;
  }
  else if (strContent.Equals("audio/flac") || strContent.Equals("audio/x-flac") || strContent.Equals("application/x-flac"))
  {
    DVDPlayerCodec *dvdcodec = new DVDPlayerCodec();
    dvdcodec->SetContentType(strContent);
    return dvdcodec;
  }

  if (urlFile.GetProtocol() == "shout")
  {
    DVDPlayerCodec *dvdcodec = new DVDPlayerCodec();
    dvdcodec->SetContentType("audio/mp3");
    return dvdcodec; // if we got this far with internet radio - content-type was wrong. gamble on mp3.
  }

  if (urlFile.GetFileType().Equals("wav") || strContent.Equals("audio/wav") || strContent.Equals("audio/x-wav"))
  {
    DVDPlayerCodec *dvdcodec = new DVDPlayerCodec();
    dvdcodec->SetContentType("audio/x-spdif-compressed");
    if (dvdcodec->Init(strFile, filecache))
    {
      return dvdcodec;
    }

    dvdcodec = new DVDPlayerCodec();
    dvdcodec->SetContentType(strContent);
    return dvdcodec;
  }
  return CreateCodec(urlFile.GetFileType());
}

