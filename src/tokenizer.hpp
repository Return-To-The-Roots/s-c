// $Id: tokenizer.hpp 7521 2011-09-08 20:45:55Z FloSoft $
//
// Copyright (c) 2005 - 2011 FloSoft (webmaster at ma.ra-doersch.de)
//
// This file is part of Siedler II.5 RTTR.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option) any
// later version.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
#ifndef TOKENIZER_HPP_INCLUDED
#define TOKENIZER_HPP_INCLUDED

#pragma once

#include <string>

/// Tokenizer-Klasse.
class tokenizer
{
public:
    /// Konstruktor von @p tokenizer.
	/**
	 *  Konstruktor von @p tokenizer.
	 *
	 *  @param[in] data      Daten die zerschnitten werden sollen
	 *  @param[in] delimiter Zeichen nach denen getrennt werden soll
	 *
	 *  @author FloSoft
	 */
    tokenizer(const std::string& data, const std::string& delimiter = "; \t")
		: data(data), delimiter(delimiter) 
	{
    }

    /// liefert den Status des Tokenizers.
	/**
	 *  liefert den Status des Tokenizers.
	 *
	 *  @return @p true falls noch Tokens erwartet werden können, 
	 *          @p false falls der interne String leer ist.
	 *
	 *  @author FloSoft
	 */
    operator bool(void) const
	{
        return data.length() > 0; 
    }

    /// extrahiert das nächste Token.
	/**
	 *  extrahiert das nächste Token.
	 *
	 *  @return das nächste Token
	 *
	 *  @author FloSoft
	 */
    std::string next(void)
	{
        std::string r;
        std::string::size_type p = data.find_first_of(delimiter);

		if (std::string::npos != p)
        {
            r = data.substr(0, p);
            data = data.substr(p+1);
        }
		else
        {
            r = data;
            data.erase();
        }
        return r;
    }
private:
	/// der Interne Datenstring.
	/**
	 *  der Interne Datenstring.
	 *
	 *  @author FloSoft
	 */
    std::string data;

	/// der Delimeterstring.
	/**
	 *  der Delimeterstring. 
	 *  Jedes Zeichen darin wird zum Trennen der Tokens benutzt.
	 *
	 *  @author FloSoft
	 */
    std::string delimiter;
};

#endif // !TOKENIZER_HPP_INCLUDED
