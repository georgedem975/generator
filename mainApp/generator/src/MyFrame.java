import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class MyFrame extends JFrame {

    private int width;

    private int height;

    private final String title;

    private boolean resizable;

    private final boolean visible;

    private final ImageIcon imageIcon;

    private Color backgroundColor;

    public MyFrame(String title,
                   int width,
                   int height,
                   boolean resizable,
                   boolean visible,
                   ImageIcon imageIcon,
                   Color backgroundColor) {
        if (title == null)
            throw new NullPointerException("title is not null");

        if (width <= 0)
            throw new NullPointerException("width more then 0");

        if (height <= 0)
            throw new NullPointerException("height more then 0");

        if (imageIcon == null)
            throw new NullPointerException("imageIcon is not null");

        this.title = title;
        this.height = height;
        this.width = width;
        this.resizable = resizable;
        this.visible = visible;
        this.backgroundColor = backgroundColor;
        this.imageIcon = imageIcon;

        this.Init();
    }

    public void addTextField(int width, int height, int tracker)
    {
        JTextField textField = new JTextField();
        textField.setPreferredSize(new Dimension(width, height));
        textField.setFont(new Font("Consolas", Font.PLAIN, tracker));

        this.add(textField);
        this.pack();
        this.setVisible(true);
    }

    public void addButton(int x,
                          int y,
                          int width,
                          int height,
                          String text,
                          int tracker) {
        JButton button;
        button = new JButton();
        button.setBounds(x, y, width, height);
        button.addActionListener((ActionListener) this);
        button.setText(text);
        button.setFocusable(false);
        button.setHorizontalTextPosition(JButton.CENTER);
        button.setVerticalTextPosition(JButton.CENTER);
        button.setFont(new Font("Comic Sans", Font.BOLD, tracker));
        button.setForeground(Color.cyan);
        button.setBackground(Color.LIGHT_GRAY);
        button.setBorder(BorderFactory.createEtchedBorder());
    }

    private void Init() {
        this.setTitle(this.title);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(this.resizable);
        this.setSize(this.width, this.height);
        this.setVisible(this.visible);

        this.setIconImage(this.imageIcon.getImage());

        this.getContentPane().setBackground(this.backgroundColor);
    }
}
