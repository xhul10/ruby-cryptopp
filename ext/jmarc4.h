/*
   +----------------------------------------------------------------------+
   | Copyright (c) 2002-2009 J Smith <dark.panda@gmail.com>               |
   | Crypto++ sources (not included) copyright (c) 1995-2009 Wei Dai      |
   +----------------------------------------------------------------------+
   | Check out COPYING for the exact license.                             |
   +----------------------------------------------------------------------+

$Id: $
*/

#ifndef __JMARC4_H__
#define __JMARC4_H__

#include "jconfig.h"

#if ENABLED_MARC4_CIPHER

#ifndef CRYPTOPP_ENABLE_NAMESPACE_WEAK
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#endif

#include "jstream_t.h"

// Crypto++ headers...

#include "arc4.h"

using namespace CryptoPP;

class JMARC4 : public JStream_Template<Weak::MARC4_Base, MARC4_CIPHER>
{
	protected:
		SymmetricCipher* getEncryptionObject();
		SymmetricCipher* getDecryptionObject();
};

#undef CRYPTOPP_ENABLE_NAMESPACE_WEAK

#endif
#endif
