CBOR-CPP
========

CBOR C++ serialization library

Just a simple SAX-like Concise Binary Object Representation (CBOR).

[http://tools.ietf.org/html/rfc7049](http://tools.ietf.org/html/rfc7049)

#### Examples

Writing:

```C++
  CborDynamicOutput output;
  CborWriter writer(output);

  writer.writeTag(123);
  writer.writeArray(3);
  writer.writeString("hello");
  writer.writeString("world");
  writer.writeInt(321);

  unsigned char *data = output.getData();
  size_t size = output.getSize();
```

Reading:

```C++
  class CborExampleListener : public CborListener {
  public:
    virtual void OnInteger(const int32_t value);
    virtual void OnByteString(unsigned char *data, const size_t size);
    virtual void OnTextString(char *data, const size_t size);
    virtual void OnArray(const size_t size);
    virtual void OnMap(const size_t size);
    virtual OnTag(const uint32_t tag);
    virtual void OnError(const char *error);
  };

  ...

  void CborExampleListener::OnInteger(const int32_t value) {
    printf("Integer: %d\n", value);
  }

  void CborExampleListener::OnByteString(unsigned char *data, const size_t size) {
    printf("Byte string of size: %d", size);
  }

  void CborExampleListener::OnTextString(char *data, const size_t size) {
    printf("UTF-8 string of size: %d", size);
  }

  void CborExampleListener::OnArray(const size_t size) {
    printf("Array of size: %d\n", size);
  }

  void CborExampleListener::OnMap(const size_t size) {
    printf("Map of size: %d\n", size);
  }

  void CborExampleListener::OnTag(const uint32_t tag) {
    printf("Tag: %d\n", tag);
  }

  void CborExampleListener::OnError(const char *error) {
    printf("Error: %s\n", error);
  }
  
  ...
  CborInput input(data, size);
  CborReader reader(input);
  CborExampleListener listener;
  reader.SetListener(listener);
  reader.Run();
```
