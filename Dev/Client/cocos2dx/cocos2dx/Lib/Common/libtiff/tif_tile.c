/* $Id: tif_tile.c,v 1.23 2012-06-06 05:33:55 fwarmerdam Exp $ */

/*
 * Copyright (c) 1991-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

/*
 * TIFF Library.
 *
 * Tiled Image Support Routines.
 */
#include "tiffiop.h"

/*
 * Compute which tile an (x,y,z,s) value is in.
 */
TIFF_UINT32_T
TIFFComputeTile(TIFF* tif, TIFF_UINT32_T x, TIFF_UINT32_T y, TIFF_UINT32_T z, TIFF_UINT16_T s)
{
	TIFFDirectory *td = &tif->tif_dir;
	TIFF_UINT32_T dx = td->td_tilewidth;
	TIFF_UINT32_T dy = td->td_tilelength;
	TIFF_UINT32_T dz = td->td_tiledepth;
	TIFF_UINT32_T tile = 1;

	if (td->td_imagedepth == 1)
		z = 0;
	if (dx == (TIFF_UINT32_T) -1)
		dx = td->td_imagewidth;
	if (dy == (TIFF_UINT32_T) -1)
		dy = td->td_imagelength;
	if (dz == (TIFF_UINT32_T) -1)
		dz = td->td_imagedepth;
	if (dx != 0 && dy != 0 && dz != 0) {
		TIFF_UINT32_T xpt = TIFFhowmany_32(td->td_imagewidth, dx);
		TIFF_UINT32_T ypt = TIFFhowmany_32(td->td_imagelength, dy);
		TIFF_UINT32_T zpt = TIFFhowmany_32(td->td_imagedepth, dz);

		if (td->td_planarconfig == PLANARCONFIG_SEPARATE) 
			tile = (xpt*ypt*zpt)*s +
			     (xpt*ypt)*(z/dz) +
			     xpt*(y/dy) +
			     x/dx;
		else
			tile = (xpt*ypt)*(z/dz) + xpt*(y/dy) + x/dx;
	}
	return (tile);
}

/*
 * Check an (x,y,z,s) coordinate
 * against the image bounds.
 */
int
TIFFCheckTile(TIFF* tif, TIFF_UINT32_T x, TIFF_UINT32_T y, TIFF_UINT32_T z, TIFF_UINT16_T s)
{
	TIFFDirectory *td = &tif->tif_dir;

	if (x >= td->td_imagewidth) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Col out of range, max %lu",
			     (unsigned long) x,
			     (unsigned long) (td->td_imagewidth - 1));
		return (0);
	}
	if (y >= td->td_imagelength) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Row out of range, max %lu",
			     (unsigned long) y,
			     (unsigned long) (td->td_imagelength - 1));
		return (0);
	}
	if (z >= td->td_imagedepth) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Depth out of range, max %lu",
			     (unsigned long) z,
			     (unsigned long) (td->td_imagedepth - 1));
		return (0);
	}
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE &&
	    s >= td->td_samplesperpixel) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "%lu: Sample out of range, max %lu",
			     (unsigned long) s,
			     (unsigned long) (td->td_samplesperpixel - 1));
		return (0);
	}
	return (1);
}

/*
 * Compute how many tiles are in an image.
 */
TIFF_UINT32_T
TIFFNumberOfTiles(TIFF* tif)
{
	TIFFDirectory *td = &tif->tif_dir;
	TIFF_UINT32_T dx = td->td_tilewidth;
	TIFF_UINT32_T dy = td->td_tilelength;
	TIFF_UINT32_T dz = td->td_tiledepth;
	TIFF_UINT32_T ntiles;

	if (dx == (TIFF_UINT32_T) -1)
		dx = td->td_imagewidth;
	if (dy == (TIFF_UINT32_T) -1)
		dy = td->td_imagelength;
	if (dz == (TIFF_UINT32_T) -1)
		dz = td->td_imagedepth;
	ntiles = (dx == 0 || dy == 0 || dz == 0) ? 0 :
	    _TIFFMultiply32(tif, _TIFFMultiply32(tif, TIFFhowmany_32(td->td_imagewidth, dx),
	    TIFFhowmany_32(td->td_imagelength, dy),
	    "TIFFNumberOfTiles"),
	    TIFFhowmany_32(td->td_imagedepth, dz), "TIFFNumberOfTiles");
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE)
		ntiles = _TIFFMultiply32(tif, ntiles, td->td_samplesperpixel,
		    "TIFFNumberOfTiles");
	return (ntiles);
}

/*
 * Compute the # bytes in each row of a tile.
 */
TIFF_UINT64_T
TIFFTileRowSize64(TIFF* tif)
{
	TIFFDirectory *td = &tif->tif_dir;
	TIFF_UINT64_T rowsize;

	if (td->td_tilelength == 0 || td->td_tilewidth == 0)
		return (0);
	rowsize = _TIFFMultiply64(tif, td->td_bitspersample, td->td_tilewidth,
	    "TIFFTileRowSize");
	if (td->td_planarconfig == PLANARCONFIG_CONTIG)
		rowsize = _TIFFMultiply64(tif, rowsize, td->td_samplesperpixel,
		    "TIFFTileRowSize");
	return (TIFFhowmany8_64(rowsize));
}
tmsize_t
TIFFTileRowSize(TIFF* tif)
{
	static const char module[] = "TIFFTileRowSize";
	TIFF_UINT64_T m;
	tmsize_t n;
	m=TIFFTileRowSize64(tif);
	n=(tmsize_t)m;
	if ((TIFF_UINT64_T)n!=m)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		n=0;
	}
	return(n);
}

/*
 * Compute the # bytes in a variable length, row-aligned tile.
 */
TIFF_UINT64_T
TIFFVTileSize64(TIFF* tif, TIFF_UINT32_T nrows)
{
	static const char module[] = "TIFFVTileSize64";
	TIFFDirectory *td = &tif->tif_dir;
	if (td->td_tilelength == 0 || td->td_tilewidth == 0 ||
	    td->td_tiledepth == 0)
		return (0);
	if ((td->td_planarconfig==PLANARCONFIG_CONTIG)&&
	    (td->td_photometric==PHOTOMETRIC_YCBCR)&&
	    (td->td_samplesperpixel==3)&&
	    (!isUpSampled(tif)))
	{
		/*
		 * Packed YCbCr data contain one Cb+Cr for every
		 * HorizontalSampling*VerticalSampling Y values.
		 * Must also roundup width and height when calculating
		 * since images that are not a multiple of the
		 * horizontal/vertical subsampling area include
		 * YCbCr data for the extended image.
		 */
		TIFF_UINT16_T ycbcrsubsampling[2];
		TIFF_UINT16_T samplingblock_samples;
		TIFF_UINT32_T samplingblocks_hor;
		TIFF_UINT32_T samplingblocks_ver;
		TIFF_UINT64_T samplingrow_samples;
		TIFF_UINT64_T samplingrow_size;
		TIFFGetFieldDefaulted(tif,TIFFTAG_YCBCRSUBSAMPLING,ycbcrsubsampling+0,
		    ycbcrsubsampling+1);
		if ((ycbcrsubsampling[0] != 1 && ycbcrsubsampling[0] != 2 && ycbcrsubsampling[0] != 4)
		    ||(ycbcrsubsampling[1] != 1 && ycbcrsubsampling[1] != 2 && ycbcrsubsampling[1] != 4))
		{
			TIFFErrorExt(tif->tif_clientdata,module,
				     "Invalid YCbCr subsampling (%dx%d)", 
				     ycbcrsubsampling[0], 
				     ycbcrsubsampling[1] );
			return 0;
		}
		samplingblock_samples=ycbcrsubsampling[0]*ycbcrsubsampling[1]+2;
		samplingblocks_hor=TIFFhowmany_32(td->td_tilewidth,ycbcrsubsampling[0]);
		samplingblocks_ver=TIFFhowmany_32(nrows,ycbcrsubsampling[1]);
		samplingrow_samples=_TIFFMultiply64(tif,samplingblocks_hor,samplingblock_samples,module);
		samplingrow_size=TIFFhowmany8_64(_TIFFMultiply64(tif,samplingrow_samples,td->td_bitspersample,module));
		return(_TIFFMultiply64(tif,samplingrow_size,samplingblocks_ver,module));
	}
	else
		return(_TIFFMultiply64(tif,nrows,TIFFTileRowSize64(tif),module));
}
tmsize_t
TIFFVTileSize(TIFF* tif, TIFF_UINT32_T nrows)
{
	static const char module[] = "TIFFVTileSize";
	TIFF_UINT64_T m;
	tmsize_t n;
	m=TIFFVTileSize64(tif,nrows);
	n=(tmsize_t)m;
	if ((TIFF_UINT64_T)n!=m)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		n=0;
	}
	return(n);
}

/*
 * Compute the # bytes in a row-aligned tile.
 */
TIFF_UINT64_T
TIFFTileSize64(TIFF* tif)
{
	return (TIFFVTileSize64(tif, tif->tif_dir.td_tilelength));
}
tmsize_t
TIFFTileSize(TIFF* tif)
{
	static const char module[] = "TIFFTileSize";
	TIFF_UINT64_T m;
	tmsize_t n;
	m=TIFFTileSize64(tif);
	n=(tmsize_t)m;
	if ((TIFF_UINT64_T)n!=m)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
		n=0;
	}
	return(n);
}

/*
 * Compute a default tile size based on the image
 * characteristics and a requested value.  If a
 * request is <1 then we choose a size according
 * to certain heuristics.
 */
void
TIFFDefaultTileSize(TIFF* tif, TIFF_UINT32_T* tw, TIFF_UINT32_T* th)
{
	(*tif->tif_deftilesize)(tif, tw, th);
}

void
_TIFFDefaultTileSize(TIFF* tif, TIFF_UINT32_T* tw, TIFF_UINT32_T* th)
{
	(void) tif;
	if (*(TIFF_INT32_T*) tw < 1)
		*tw = 256;
	if (*(TIFF_INT32_T*) th < 1)
		*th = 256;
	/* roundup to a multiple of 16 per the spec */
	if (*tw & 0xf)
		*tw = TIFFroundup_32(*tw, 16);
	if (*th & 0xf)
		*th = TIFFroundup_32(*th, 16);
}

/* vim: set ts=8 sts=8 sw=8 noet: */
/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * fill-column: 78
 * End:
 */
