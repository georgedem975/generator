import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyFrame extends JFrame implements ActionListener {

    private int width;

    private int height;

    private final String title;

    private boolean resizable;

    private final boolean visible;

    private final ImageIcon imageIcon;

    private Color backgroundColor;

    private JButton button;

    private JComboBox box;

    private JTextField textField;

    private CGenerator generator;

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

        this.generator = new CGenerator();

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
        button = new JButton();
        button.setBounds(x, y, width, height);
        button.addActionListener(this);
        button.setText(text);
        button.setFocusable(false);
        button.setHorizontalTextPosition(JButton.CENTER);
        button.setVerticalTextPosition(JButton.CENTER);
        button.setFont(new Font("Comic Sans", Font.BOLD, tracker));
        button.setForeground(Color.cyan);
        button.setBackground(Color.LIGHT_GRAY);
        button.setBorder(BorderFactory.createEtchedBorder());
        this.add(button);
    }

    private void Init() {
        this.setTitle(this.title);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(this.resizable);
        this.setSize(this.width, this.height);
        this.setVisible(this.visible);

        this.setIconImage(this.imageIcon.getImage());

        this.getContentPane().setBackground(this.backgroundColor);

        String positions[] = { "midpoint displacement", "diamond square"};
        box = new JComboBox(positions);
        box.setBounds(40, 40, 130, 20);
        this.add(box);
        this.setSize(400, 400);
        this.setLayout(null);
        this.setVisible(true);

        textField = new JTextField("path");
        textField.setBounds(40, 80, 200, 30);
        this.add(textField);
        this.setSize(300, 300);
        this.setLayout(null);
        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == this.button){
            if (this.box.getSelectedItem() == "midpoint displacement"){
                generator.generateImageByDSMD();
                WriterImage writerImage = new WriterImage();
                writerImage.writeImage(this.textField.getText(), this.generator);
            }
            else {
                generator.generateImageByDS();
                WriterImage writerImage = new WriterImage();
                writerImage.writeImage(this.textField.getText(), this.generator);
            }
        }
    }
}
