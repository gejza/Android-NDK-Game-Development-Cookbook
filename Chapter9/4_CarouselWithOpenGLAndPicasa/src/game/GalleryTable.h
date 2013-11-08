/*
 * Copyright (C) 2013 Sergey Kosarevsky (sk@linderdaum.com)
 * Copyright (C) 2013 Viktor Latypov (vl@linderdaum.com)
 * Based on Linderdaum Engine http://www.linderdaum.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must display the names 'Sergey Kosarevsky' and
 *    'Viktor Latypov'in the credits of the application, if such credits exist.
 *    The authors of this work must be notified via email (sk@linderdaum.com) in 
 *    this case of redistribution.
 *
 * 3. Neither the name of copyright holders nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "iObject.h"
#include "ImageTypes.h"
#include "Picasa.h"

class Blob;

class clGallery: public iObject
{
public:
	clGallery(): FNoImagesList( true ) {}

	/// Get fullsize URL for this image
	std::string GetFullSizeURL( int Idx ) const
	{
		return ( Idx < ( int )FURLs.size() ) ? Picasa_GetDirectImageURL( FURLs[Idx], L_PHOTO_SIZE_ORIGINAL ) : std::string();
	}

	size_t            GetTotalImages() const { return FImages.size(); }
	clPtr<sImageDescriptor> GetImage( size_t Idx ) const { return ( Idx < FImages.size() ) ? FImages[Idx] : NULL; };

	void CancellAllDownloads();
	// restart downloading of all images that are not loaded
	void ResetAllDownloads();
	bool StartListDownload();

	/// Callback for start list download
	void ListDownloaded( clPtr<clBlob> Blob );
private:
	/// Internal state: loaded list of images
	bool FNoImagesList;

	/// Base URLs of the images
	std::vector<std::string> FURLs;

	/// Complete list of the images being loaded
	std::vector< clPtr<sImageDescriptor> > FImages;
};