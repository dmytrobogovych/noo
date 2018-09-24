#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QByteArray>
#include <openssl/blowfish.h>
#include <openssl/sha.h>
#include "twofish.h"

class BlowfishCipher
{
protected:
  QByteArray mKey;
  QByteArray mIV;
  BF_KEY mContext;

public:
  BlowfishCipher();
  ~BlowfishCipher();
  void setKey(const QByteArray& ba);
  const QByteArray& key() const;
  void setIV(const QByteArray& ba);
  QByteArray& IV() const;

  void encrypt(const QByteArray& plain, QByteArray& encrypted);
  void decrypt(const QByteArray& encrypted, QByteArray& plain);
};

class TwofishCipher
{
protected:
  QByteArray mKey;
  QByteArray mIV;
  TwofishKey mKeyStruct;
  Twofish* mContext;

public:
  TwofishCipher();
  ~TwofishCipher();

  int blocksize() const { return 16; }
  void setKey(const QByteArray& ba);
  const QByteArray& key() const;

  // IV vector must be 16 bytes
  void setIV(const QByteArray& ba);
  const QByteArray& IV() const;

  // Plain and encrypted must be padded to 16 bytes boundary before call
  void encrypt(const QByteArray& plain, int plainOffset, QByteArray& encrypted, int encryptedOffset);
  void decrypt(const QByteArray& encrypted, int encryptedOffset, QByteArray& plain, int plainOffset);
};


class SHA256
{
protected:
  SHA256_CTX mContext;
  QByteArray mDigest;
public:
  SHA256();
  ~SHA256();

  QByteArray& digest();
  void update(const void* data, int length);
  void final();
};

class IV
{
public:
  static void Generate(QByteArray& buffer);
};

#endif // ENCRYPTION_H
