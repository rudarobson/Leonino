/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package leoninoide;

import leoninoide.eventslistener.EditorEventListener;
import leoninoide.eventslistener.EditorEventFirer;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.*;
import javax.swing.JPanel;
import org.fife.ui.rsyntaxtextarea.RSyntaxTextArea;
import org.fife.ui.rsyntaxtextarea.SyntaxConstants;
import org.fife.ui.rtextarea.RTextScrollPane;

/**
 *
 * @author rudarobson
 */
public class EditorPanel extends JPanel implements KeyListener, EditorEventFirer {

    private RSyntaxTextArea textArea;
    private ArrayList<EditorEventListener> editorListeners;

    public EditorPanel() {
        editorListeners = new ArrayList<EditorEventListener>();

        textArea = new RSyntaxTextArea(20, 60);
        textArea.setSyntaxEditingStyle(SyntaxConstants.SYNTAX_STYLE_JAVA);
        textArea.setCodeFoldingEnabled(true);
        textArea.setAntiAliasingEnabled(true);
        textArea.addKeyListener(this);

        RTextScrollPane sp = new RTextScrollPane(textArea);
        sp.setFoldIndicatorEnabled(true);
        this.add(sp);

//        setContentPane(cp);
//        setTitle("Text Editor Demo");
//        setDefaultCloseOperation(EXIT_ON_CLOSE);
//        pack();
//        setLocationRelativeTo(null);
    }

    public void setCStyle() {
        textArea.setSyntaxEditingStyle("text/c");
    }

    public RSyntaxTextArea getTextArea() {
        return textArea;
    }

    public String getCode() {
        return textArea.getText();
    }

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
        if (e.isControlDown() && e.getKeyCode() == KeyEvent.VK_F) {
            for (Iterator<EditorEventListener> it = editorListeners.iterator(); it.hasNext();) {
                it.next().CtrlF();
            }
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
    }

    @Override
    public void addEditorListener(EditorEventListener e) {
        editorListeners.add(e);
    }
}
