public class CGenerator {
    public native void generateImageByDSMD();

    public native int getSize();

    public native int getPixelRGB(int index, char mod);

    public native void generateImageByDS();

    static
    {
        System.loadLibrary("FirstAlgorithmsDLL");
    }

    public CGenerator() { }
}
