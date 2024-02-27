package ej2.utils;

import java.io.*;

public class Converter {
    public static byte[] createByteArrayOfObject(Object object)
    {
        ByteArrayOutputStream bStream = new ByteArrayOutputStream();
        try (ObjectOutput oo = new ObjectOutputStream(bStream)){
            oo.writeObject(object);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return bStream.toByteArray();
    }

    public static Object convertBytesToObject(byte[] bytes)
    {
        try(ObjectInputStream iStream = new ObjectInputStream(new ByteArrayInputStream(bytes))) {
            return iStream.readObject();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
