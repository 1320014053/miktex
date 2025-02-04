/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LOG4CXX_HELPERS_LOCALE_H
#define _LOG4CXX_HELPERS_LOCALE_H

#include <log4cxx/logstring.h>
#include <memory>

namespace log4cxx
{
namespace helpers
{
class LOG4CXX_EXPORT Locale
{
	public:
		Locale(const LogString& language);
		Locale(const LogString& language, const LogString& country);
		Locale(const LogString& language, const LogString& country,
			const LogString& variant);
		~Locale();

		const LogString& getLanguage() const;
		const LogString& getCountry() const;
		const LogString& getVariant() const;

	protected:
		Locale(const Locale&);
		Locale& operator=(const Locale&);
		LOG4CXX_DECLARE_PRIVATE_MEMBER_PTR(LocalePrivate, m_priv)
}; // class Locale
}  // namespace helpers
} // namespace log4cxx


#endif // _LOG4CXX_HELPERS_LOCALE_H
