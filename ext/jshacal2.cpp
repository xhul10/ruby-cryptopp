
/*
 * Copyright (c) 2002-2010 J Smith <dark.panda@gmail.com>
 * Crypto++ copyright (c) 1995-2010 Wei Dai
 * See COPYING for the extact license
 */

#include "jshacal2.h"

#if ENABLED_SHACAL2_CIPHER

BlockCipher* JSHACAL2::getEncryptionObject()
{
	return new SHACAL2Encryption((byte*) itsKey.data(), itsKeylength);
}

BlockCipher* JSHACAL2::getDecryptionObject()
{
	return new SHACAL2Decryption((byte*) itsKey.data(), itsKeylength);
}

#endif
