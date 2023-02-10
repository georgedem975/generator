import javax.swing.*;
import java.awt.*;
import java.nio.file.Path;

public class Main {
    public static void main(String[] args){
        ImageIcon imageIcon = new ImageIcon(String.valueOf(Path.of("src", "logo.jpg")));

        MyFrame frame = new MyFrame("Generator",
                480, 480, false, true,
                imageIcon, Color.WHITE);

        frame.addButton(100, 120, 170, 50, "выполнить алгоритм", 15);
    }
}
