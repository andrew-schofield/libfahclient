/*
 * File PYONValue.h part of the SimplePYON Library - http://mjpa.in/PYON
 * 
 * Copyright (C) 2010 Mike Anchor
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _PYONVALUE_H_
#define _PYONVALUE_H_

#include <vector>
#include <string>

#include "PYON.h"

class PYON;

enum PYONType { PYONType_Null, PYONType_String, PYONType_Bool, PYONType_Number, PYONType_Array, PYONType_Object };

class PYONValue
{
	friend class PYON;
	
	public:
		PYONValue(/*NULL*/);
		PYONValue(const wchar_t *m_char_value);
		PYONValue(const std::wstring &m_string_value);
		PYONValue(bool m_bool_value);
		PYONValue(double m_number_value);
		PYONValue(const PYONArray &m_array_value);
		PYONValue(const PYONObject &m_object_value);
		~PYONValue();
		
		bool IsNull() const;
		bool IsString() const;
		bool IsBool() const;
		bool IsNumber() const;
		bool IsArray() const;
		bool IsObject() const;
		
		const std::wstring &AsString() const;
		bool AsBool() const;
		double AsNumber() const;
		const PYONArray &AsArray() const;
		const PYONObject &AsObject() const;
		
		std::wstring Stringify() const;
		
	protected:
		static PYONValue *Parse(const wchar_t **data);
	
	private:
		static std::wstring StringifyString(const std::wstring &str);
	
		PYONType type;
		std::wstring string_value;
		bool bool_value;
		double number_value;
		PYONArray array_value;
		PYONObject object_value;
};

#endif
