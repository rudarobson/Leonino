/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package leoninoide;

import java.util.ArrayList;
import java.util.Iterator;
import javax.swing.JOptionPane;
import leoninoide.eventslistener.ShortcutFirer;
import leoninoide.eventslistener.ShortcutListener;

/**
 *
 * @author rudarobson
 */
public class ShortcutBar extends javax.swing.JPanel implements ShortcutFirer {

    /**
     * Creates new form ShortcutBar
     */
    public ShortcutBar() {
        initComponents();
        shortcutListeners = new ArrayList<ShortcutListener>();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        verifyButton = new javax.swing.JButton();

        verifyButton.setText("Verify");
        verifyButton.setActionCommand("verify");
        verifyButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                verifyButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(19, 19, 19)
                .addComponent(verifyButton)
                .addContainerGap(434, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(verifyButton)
                .addGap(0, 14, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void verifyButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_verifyButtonActionPerformed
        for (Iterator<ShortcutListener> it = shortcutListeners.iterator(); it.hasNext();) {
            it.next().compile();
        }
    }//GEN-LAST:event_verifyButtonActionPerformed
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton verifyButton;
    // End of variables declaration//GEN-END:variables
    private ArrayList<ShortcutListener> shortcutListeners;

    @Override
    public void addShortcutListener(ShortcutListener sl) {
        shortcutListeners.add(sl);
    }
}