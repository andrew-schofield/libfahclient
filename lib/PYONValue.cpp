/*
 * File JSON.cpp part of the SimpleJSON Library - http://mjpa.in/JSON
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>

#include "PYONValue.h"

// Macros to free an array/object
#define FREE_ARRAY(x) { PYONArray::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { delete *iter; } }
#define FREE_OBJECT(x) { PYONObject::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { delete (*iter).second; } }

/**
 * Parses a PYON encoded value to a PYONValue object
 *
 * @access protected
 *
 * @param wchar_t** data Pointer to a wchar_t* that contains the data
 *
 * @return PYONValue* Returns a pointer to a PYONValue object on success, NULL on error
 */
PYONValue *PYONValue::Parse(const wchar_t **data)
{
	// Is it a string?
	if (**data == '"')
	{
		std::wstring str;
		if (!PYON::ExtractString(&(++(*data)), str))
			return NULL;
		else
			return new PYONValue(str);
	}
	
	// Is it a boolean?
	else if ((wcslen(*data) >= 4 && wcsncasecmp(*data, L"True", 4) == 0) || (wcslen(*data) >= 5 && wcsncasecmp(*data, L"False", 5) == 0))
	{
		bool value = wcsncasecmp(*data, L"True", 4) == 0;
		(*data) += value ? 4 : 5;
		return new PYONValue(value);
	}
	
	// Is it a null?
	else if (wcslen(*data) >= 4 && wcsncasecmp(*data, L"None", 4) == 0)
	{
		(*data) += 4;
		return new PYONValue();
	}
	
	// Is it a number?
	else if (**data == L'-' || (**data >= L'0' && **data <= L'9'))
	{
		// Negative?
		bool neg = **data == L'-';
		if (neg) (*data)++;

		double number = 0.0;

		// Parse the whole part of the number - only if it wasn't 0
		if (**data == L'0')
			(*data)++;
		else if (**data >= L'1' && **data <= L'9')
			number = PYON::ParseInt(data);
		else
			return NULL;
		
		// Could be a decimal now...
		if (**data == '.')
		{
			(*data)++;

			// Not get any digits?
			if (!(**data >= L'0' && **data <= L'9'))
				return NULL;
			
			// Find the decimal and sort the decimal place out
			// Use ParseDecimal as ParseInt won't work with decimals less than 0.1
			// thanks to Javier Abadia for the report & fix
			double decimal = PYON::ParseDecimal(data);
			
			// Save the number
			number += decimal;
		}

		// Could be an exponent now...
		if (**data == L'E' || **data == L'e')
		{
			(*data)++;

			// Check signage of expo
			bool neg_expo = false;
			if (**data == L'-' || **data == L'+')
			{
				neg_expo = **data == L'-';
				(*data)++;
			}
			
			// Not get any digits?
			if (!(**data >= L'0' && **data <= L'9'))
				return NULL;

			// Sort the expo out
			double expo = PYON::ParseInt(data);
			for (double i = 0.0; i < expo; i++)
				number = neg_expo ? (number / 10.0) : (number * 10.0);
		}

		// Was it neg?
		if (neg) number *= -1;

		return new PYONValue(number);
	}

	// An object?
	else if (**data == L'{')
	{
		PYONObject object;
		
		(*data)++;
	
		while (**data != 0)
		{
			// Whitespace at the start?
			if (!PYON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// Special case - empty object
			if (object.size() == 0 && **data == L'}')
			{
				(*data)++;
				return new PYONValue(object);
			}
			
			// We want a string now...
			std::wstring name;
			if (!PYON::ExtractString(&(++(*data)), name))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// More whitespace?
			if (!PYON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// Need a : now
			if (*((*data)++) != L':')
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// More whitespace?
			if (!PYON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// The value is here			
			PYONValue *value = Parse(data);
			if (value == NULL)
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// Add the name:value
			if (object.find(name) != object.end())
				delete object[name];
			object[name] = value;
			
			// More whitespace?
			if (!PYON::SkipWhitespace(data))
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			// End of object?
			if (**data == L'}')
			{
				(*data)++;
				return new PYONValue(object);
			}
			
			// Want a , now
			if (**data != L',')
			{
				FREE_OBJECT(object);
				return NULL;
			}
			
			(*data)++;
		}
		
		// Only here if we ran out of data
		FREE_OBJECT(object);
		return NULL;
	}
	
	// An array?
	else if (**data == L'[')
	{
		PYONArray array;
		
		(*data)++;
		
		while (**data != 0)
		{
			// Whitespace at the start?
			if (!PYON::SkipWhitespace(data))
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			// Special case - empty array
			if (array.size() == 0 && **data == L']')
			{
				(*data)++;
				return new PYONValue(array);
			}
			
			// Get the value
			PYONValue *value = Parse(data);
			if (value == NULL)
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			// Add the value
			array.push_back(value);
			
			// More whitespace?
			if (!PYON::SkipWhitespace(data))
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			// End of array?
			if (**data == L']')
			{
				(*data)++;
				return new PYONValue(array);
			}
			
			// Want a , now
			if (**data != L',')
			{
				FREE_ARRAY(array);
				return NULL;
			}
			
			(*data)++;
		}
		
		// Only here if we ran out of data
		FREE_ARRAY(array);
		return NULL;
	}
	
	// Ran out of possibilites, it's bad!
	else
	{
		return NULL;
	}
}

/** 
 * Basic constructor for creating a PYON Value of type NULL
 *
 * @access public
 */
PYONValue::PYONValue(/*NULL*/)
{
	type = PYONType_Null;
}

/** 
 * Basic constructor for creating a PYON Value of type String
 *
 * @access public
 *
 * @param wchar_t* m_char_value The string to use as the value
 */
PYONValue::PYONValue(const wchar_t *m_char_value)
{
	type = PYONType_String;
	string_value = std::wstring(m_char_value);
}

/** 
 * Basic constructor for creating a PYON Value of type String
 *
 * @access public
 *
 * @param std::wstring m_string_value The string to use as the value
 */
PYONValue::PYONValue(const std::wstring &m_string_value)
{
	type = PYONType_String;
	string_value = m_string_value;
}

/** 
 * Basic constructor for creating a PYON Value of type Bool
 *
 * @access public
 *
 * @param bool m_bool_value The bool to use as the value
 */
PYONValue::PYONValue(bool m_bool_value)
{
	type = PYONType_Bool;
	bool_value = m_bool_value;
}

/** 
 * Basic constructor for creating a PYON Value of type Number
 *
 * @access public
 *
 * @param double m_number_value The number to use as the value
 */
PYONValue::PYONValue(double m_number_value)
{
	type = PYONType_Number;
	number_value = m_number_value;
}

/** 
 * Basic constructor for creating a PYON Value of type Array
 *
 * @access public
 *
 * @param PYONArray m_array_value The PYONArray to use as the value
 */
PYONValue::PYONValue(const PYONArray &m_array_value)
{
	type = PYONType_Array;
	array_value = m_array_value;
}

/** 
 * Basic constructor for creating a PYON Value of type Object
 *
 * @access public
 *
 * @param PYONObject m_object_value The PYONObject to use as the value
 */
PYONValue::PYONValue(const PYONObject &m_object_value)
{
	type = PYONType_Object;
	object_value = m_object_value;
}

/** 
 * The destructor for the PYON Value object
 * Handles deleting the objects in the array or the object value
 *
 * @access public
 */
PYONValue::~PYONValue()
{
	if (type == PYONType_Array)
	{
		PYONArray::iterator iter;
		for (iter = array_value.begin(); iter != array_value.end(); iter++)
			delete *iter;
	}
	else if (type == PYONType_Object)
	{
		PYONObject::iterator iter;
		for (iter = object_value.begin(); iter != object_value.end(); iter++)
		{
			delete (*iter).second;
		}
	}
}

/** 
 * Checks if the value is a NULL
 *
 * @access public
 *
 * @return bool Returns true if it is a NULL value, false otherwise
 */
bool PYONValue::IsNull() const
{
	return type == PYONType_Null;
}

/** 
 * Checks if the value is a String
 *
 * @access public
 *
 * @return bool Returns true if it is a String value, false otherwise
 */
bool PYONValue::IsString() const
{
	return type == PYONType_String;
}

/** 
 * Checks if the value is a Bool
 *
 * @access public
 *
 * @return bool Returns true if it is a Bool value, false otherwise
 */
bool PYONValue::IsBool() const
{
	return type == PYONType_Bool;
}

/** 
 * Checks if the value is a Number
 *
 * @access public
 *
 * @return bool Returns true if it is a Number value, false otherwise
 */
bool PYONValue::IsNumber() const
{
	return type == PYONType_Number;
}

/** 
 * Checks if the value is an Array
 *
 * @access public
 *
 * @return bool Returns true if it is an Array value, false otherwise
 */
bool PYONValue::IsArray() const
{
	return type == PYONType_Array;
}

/** 
 * Checks if the value is an Object
 *
 * @access public
 *
 * @return bool Returns true if it is an Object value, false otherwise
 */
bool PYONValue::IsObject() const
{
	return type == PYONType_Object;
}

/** 
 * Retrieves the String value of this PYONValue
 * Use IsString() before using this method.
 *
 * @access public
 *
 * @return std::wstring Returns the string value
 */
const std::wstring &PYONValue::AsString() const
{
	return string_value;
}

/** 
 * Retrieves the Bool value of this PYONValue
 * Use IsBool() before using this method.
 *
 * @access public
 *
 * @return bool Returns the bool value
 */
bool PYONValue::AsBool() const
{
	return bool_value;
}

/** 
 * Retrieves the Number value of this PYONValue
 * Use IsNumber() before using this method.
 *
 * @access public
 *
 * @return double Returns the number value
 */
double PYONValue::AsNumber() const
{
	return number_value;
}

/** 
 * Retrieves the Array value of this PYONValue
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return PYONArray Returns the array value
 */
const PYONArray &PYONValue::AsArray() const
{
	return array_value;
}

/** 
 * Retrieves the Object value of this PYONValue
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return PYONObject Returns the object value
 */
const PYONObject &PYONValue::AsObject() const
{
	return object_value;
}

/** 
 * Creates a PYON encoded string for the value with all necessary characters escaped
 *
 * @access public
 *
 * @return std::wstring Returns the PYON string
 */
std::wstring PYONValue::Stringify() const
{
	std::wstring ret_string;
	
	switch (type)
	{
		case PYONType_Null:
			ret_string = L"None";
			break;
		
		case PYONType_String:
			ret_string = StringifyString(string_value);
			break;
		
		case PYONType_Bool:
			ret_string = bool_value ? L"True" : L"False";
			break;
		
		case PYONType_Number:
		{
			if (isinf(number_value) || isnan(number_value))
				ret_string = L"None";
			else
			{
				std::wstringstream ss;
				ss << number_value;
				ret_string = ss.str();
			}
			break;
		}
		
		case PYONType_Array:
		{
			ret_string = L"[";
			PYONArray::const_iterator iter = array_value.begin();
			while (iter != array_value.end())
			{
				ret_string += (*iter)->Stringify();
				
				// Not at the end - add a separator
				if (++iter != array_value.end())
					ret_string += L",";
			}
			ret_string += L"]";
			break;
		}
		
		case PYONType_Object:
		{
			ret_string = L"{";
			PYONObject::const_iterator iter = object_value.begin();
			while (iter != object_value.end())
			{
				ret_string += StringifyString((*iter).first);
				ret_string += L":";
				ret_string += (*iter).second->Stringify();
				
				// Not at the end - add a separator
				if (++iter != object_value.end())
					ret_string += L",";
			}
			ret_string += L"}";
			break;
		}
	}

	return ret_string;
}

/** 
 * Creates a PYON encoded string with all required fields escaped
 * Works from http://www.ecma-internationl.org/publications/files/ECMA-ST/ECMA-262.pdf
 * Section 15.12.3.
 *
 * @access private
 *
 * @param std::wstring str The string that needs to have the characters escaped
 *
 * @return std::wstring Returns the PYON string
 */
std::wstring PYONValue::StringifyString(const std::wstring &str)
{
	std::wstring str_out = L"\"";
	
	std::wstring::const_iterator iter = str.begin();
	while (iter != str.end())
	{
		wchar_t chr = *iter;

		if (chr == L'"' || chr == L'\\' || chr == L'/')
		{
			str_out += L'\\';
			str_out += chr;
		}
		else if (chr == L'\b')
		{
			str_out += L"\\b";
		}
		else if (chr == L'\f')
		{
			str_out += L"\\f";
		}
		else if (chr == L'\n')
		{
			str_out += L"\\n";
		}
		else if (chr == L'\r')
		{
			str_out += L"\\r";
		}
		else if (chr == L'\t')
		{
			str_out += L"\\t";
		}
		else if (chr < L' ')
		{
			str_out += L"\\u";
			for (int i = 0; i < 4; i++)
			{
				int value = (chr >> 12) & 0xf;
				if (value >= 0 && value <= 9)
					str_out += (wchar_t)('0' + value);
				else if (value >= 10 && value <= 15)
					str_out += (wchar_t)('A' + (value - 10));
				chr <<= 4;
			}
		}
		else
		{
			str_out += chr;
		}
		
		iter++;
	}
	
	str_out += L"\"";
	return str_out;
}
