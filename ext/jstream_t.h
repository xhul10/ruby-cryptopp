
/*
 * Copyright (c) 2002-2013 J Smith <dark.panda@gmail.com>
 * Crypto++ copyright (c) 1995-2013 Wei Dai
 * See COPYING for the extact license
 */

#ifndef __JSTREAM_T_H__
#define __JSTREAM_T_H__

#include "jbasiccipherinfo.h"

template <typename INFO, enum CipherEnum TYPE>
class JStream_Template : public JBasicCipherInfo<INFO, JStream>
{
  public:
    JStream_Template();

    inline enum CipherEnum getCipherType() const;
    inline unsigned int getBlockSize() const { return 0; }

    bool encrypt();
    bool decrypt();

    bool encryptRubyIO(VALUE* in, VALUE* out);
    bool decryptRubyIO(VALUE* in, VALUE* out);

    /* These are deprecated. They were used before using php_streams. Use them
       if you're using this code in something other than the cryptopp PHP
       extension...*/
    // bool encryptFile(const string in, const string out);
    // bool decryptFile(const string in, const string out);

  protected:
    virtual SymmetricCipher* getEncryptionObject() = 0;
    virtual SymmetricCipher* getDecryptionObject() = 0;
};

template <typename INFO, enum CipherEnum TYPE>
JStream_Template<INFO, TYPE>::JStream_Template()
{
  this->itsKeylength = INFO::DEFAULT_KEYLENGTH;
}

template <typename INFO, enum CipherEnum TYPE>
CipherEnum JStream_Template<INFO, TYPE>::getCipherType() const
{
  return TYPE;
}

template <typename INFO, enum CipherEnum TYPE>
bool JStream_Template<INFO, TYPE>::encrypt()
{
  StreamTransformation* cipher = NULL;

  cipher = getEncryptionObject();

  if (cipher != NULL) {
    this->itsCiphertext.erase();
    StringSource(this->itsPlaintext, true, new StreamTransformationFilter(*cipher, new StringSink(this->itsCiphertext)));
    delete cipher;
    return true;
  }
  else {
    return false;
  }
}

template <typename INFO, enum CipherEnum TYPE>
bool JStream_Template<INFO, TYPE>::decrypt()
{
  StreamTransformation* cipher = NULL;

  cipher = getDecryptionObject();

  if (cipher != NULL) {
    this->itsPlaintext.erase();
    StringSource(this->itsCiphertext, true, new StreamTransformationFilter(*cipher, new StringSink(this->itsPlaintext)));
    delete cipher;
    return true;
  }
  else {
    return false;
  }
}

template <typename INFO, enum CipherEnum TYPE>
bool JStream_Template<INFO, TYPE>::encryptRubyIO(VALUE* in, VALUE* out)
{
  StreamTransformation* cipher = NULL;

  cipher = getEncryptionObject();

  if (cipher != NULL) {
    try {
      RubyIOSource(&in, true, new StreamTransformationFilter(*cipher, new RubyIOSink(&out)));
    }
    catch (RubyIOStore::OpenErr e) {
      delete cipher;
      throw e;
    }
    delete cipher;
  }

  return true;
}

template <typename INFO, enum CipherEnum TYPE>
bool JStream_Template<INFO, TYPE>::decryptRubyIO(VALUE* in, VALUE* out)
{
  StreamTransformation* cipher = NULL;

  cipher = getDecryptionObject();

  if (cipher != NULL) {
    try {
      RubyIOSource(&in, true, new StreamTransformationFilter(*cipher, new RubyIOSink(&out)));
    }
    catch (RubyIOStore::OpenErr e) {
      delete cipher;
      throw e;
    }
    delete cipher;
  }

  return true;
}

/* These are deprecated. They were used before using php_streams. Use them
   if you're using this code in something other than the cryptopp PHP
   extension... */
/*template <typename INFO, enum CipherEnum TYPE>
bool JStream_Template<INFO, TYPE>::encryptFile(const string in, const string out)
{
  StreamTransformation* cipher = NULL;

  cipher = getEncryptionObject();

  if (cipher != NULL) {
    try {
      FileSource(in.c_str(), true, new StreamTransformationFilter(*cipher, new FileSink(out.c_str())));
    }
    catch (FileStore::OpenErr e) {
      delete cipher;
      throw e;
    }
    delete cipher;
  }

  return true;
}

template <typename INFO, enum CipherEnum TYPE>
bool JStream_Template<INFO, TYPE>::decryptFile(const string in, const string out)
{
  StreamTransformation* cipher = NULL;

  cipher = getDecryptionObject();

  if (cipher != NULL) {
    try {
      FileSource(in.c_str(), true, new StreamTransformationFilter(*cipher, new FileSink(out.c_str())));
    }
    catch (FileStore::OpenErr e) {
      delete cipher;
      throw e;
    }
    delete cipher;
  }

  return true;
}
*/

#endif
