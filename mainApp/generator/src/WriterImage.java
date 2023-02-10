import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class WriterImage {
    public void writeImage(String path, CGenerator generator){
        BufferedImage img= new BufferedImage(30, 30, BufferedImage.TYPE_INT_RGB);
            for (int r = 0; r < 30; r++)
                for (int c = 0; c < 30; c++)
                {
                    int red = generator.getPixelRGB(c * r + c, 'r');
                    int green = generator.getPixelRGB(c * r + c, 'g');
                    int blue = generator.getPixelRGB(c * r + c, 'b');
                    int rgb = (red << 16) | (green << 8) | blue;
                    img.setRGB(c, r, rgb);
                }
        try {
            ImageIO.write(img,"jpg", new File(path));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
