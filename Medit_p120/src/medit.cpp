/***************************************************************************
 *   Copyright (C) 2008 by Graham Morrison   *
 *   graham.morrison@futurenet.co.uk   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#define OFFSET_NAME			63
#define OFFSET_CATEGORY		86


#include <QtGui>
#include "medit.h"
#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"
#include "combodelegate.h"

#include <QTextEdit>
#include <QTextStream>
#include <QCloseEvent>
#include <QFileDialog>

// GM Added
#include <QVariant>
#include <QByteArray>
#include <QBitArray>
#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QComboBox>
#include <iostream>

medit::medit()
{

	  QMainWindow::setUnifiedTitleAndToolBarOnMac(true); 
      textEdit = new QTextEdit;
	  
// GM Added
      treeView = new QTreeView;
	  model = new QStandardItemModel();
	  model->setColumnCount(3);
	  model->setHeaderData(0, Qt::Horizontal, tr("Name"));
      model->setHeaderData(1, Qt::Horizontal, tr("Type"));
      model->setHeaderData(2, Qt::Horizontal, tr("Rating"));

	  treeView->setModel(model);	    
	  treeView->setItemDelegateForColumn(1, new ComboDelegate);	  
	  treeView->setItemDelegateForColumn(2, new StarDelegate);

	  treeView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
	  treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
	  
	  treeView->setSortingEnabled(true);
	  treeView->header()->setResizeMode(0, QHeaderView::Stretch);
	  treeView->header()->setResizeMode(1, QHeaderView::Stretch);
	  treeView->header()->setResizeMode(2, QHeaderView::Stretch);
	  
      setCentralWidget(treeView);

      createActions();
      createMenus();
      createToolBars();
      createStatusBar();
      
      readSettings();
      
//      connect(textEdit->document(), SIGNAL(contentsChanged()),
//            this, SLOT(documentWasModified()));
      
      setCurrentFile("");
}

void medit::closeEvent(QCloseEvent *event)
{
      if (maybeSave()) {
            writeSettings();
            event->accept();
      } else {
            event->ignore();
      }
}

void medit::newFile()
{
      if (maybeSave()) {
            textEdit->clear();
            setCurrentFile("");
      }
}

void medit::open()
{
      if (maybeSave()) {
            QString fileName = QFileDialog::getOpenFileName(this);
            if (!fileName.isEmpty())
            loadFile(fileName);
      }
}

bool medit::save()
{
      if (curFile.isEmpty()) {
            return saveAs();
      } else {
            return saveFile(curFile);
      }
}

bool medit::saveAs()
{
      QString fileName = QFileDialog::getSaveFileName(this);
      if (fileName.isEmpty())
            return false;

      return saveFile(fileName);
}

void medit::about()
{
      QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
                  "write modern GUI applications using Qt, with a menu bar, "
                  "toolbars, and a status bar."));
}

void medit::documentWasModified()
{
      setWindowModified(true);
}

void medit::createActions()
{
      newAct = new QAction(QIcon(":/images/filenew.png"), tr("&New"), this);
      newAct->setShortcut(tr("Ctrl+N"));
      newAct->setStatusTip(tr("Create a new file"));
      connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

      openAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Open..."), this);
      openAct->setShortcut(tr("Ctrl+O"));
      openAct->setStatusTip(tr("Open an existing file"));
      connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

      saveAct = new QAction(QIcon(":/images/filesave.png"), tr("&Save"), this);
      saveAct->setShortcut(tr("Ctrl+S"));
      saveAct->setStatusTip(tr("Save the document to disk"));
      connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

      saveAsAct = new QAction(tr("Save &As..."), this);
      saveAsAct->setStatusTip(tr("Save the document under a new name"));
      connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

      exitAct = new QAction(tr("E&xit"), this);
      exitAct->setShortcut(tr("Ctrl+Q"));
      exitAct->setStatusTip(tr("Exit the application"));
      connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

      cutAct = new QAction(QIcon(":/images/editcut.png"), tr("Cu&t"), this);
      cutAct->setShortcut(tr("Ctrl+X"));
      cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                              "clipboard"));
      connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

      copyAct = new QAction(QIcon(":/images/editcopy.png"), tr("&Copy"), this);
      copyAct->setShortcut(tr("Ctrl+C"));
      copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                              "clipboard"));
      connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

      pasteAct = new QAction(QIcon(":/images/editpaste.png"), tr("&Paste"), this);
      pasteAct->setShortcut(tr("Ctrl+V"));
      pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
      connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

      aboutAct = new QAction(tr("&About"), this);
      aboutAct->setStatusTip(tr("Show the application's About box"));
      connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

      aboutQtAct = new QAction(tr("About &Qt"), this);
      aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
      connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

      cutAct->setEnabled(false);
      copyAct->setEnabled(false);
      connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
      connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
}

void medit::createMenus()
{
      fileMenu = menuBar()->addMenu(tr("&File"));
      fileMenu->addAction(newAct);
      fileMenu->addAction(openAct);
      fileMenu->addAction(saveAct);
      fileMenu->addAction(saveAsAct);
      fileMenu->addSeparator();
      fileMenu->addAction(exitAct);

      editMenu = menuBar()->addMenu(tr("&Edit"));
      editMenu->addAction(cutAct);
      editMenu->addAction(copyAct);
      editMenu->addAction(pasteAct);

      menuBar()->addSeparator();

      helpMenu = menuBar()->addMenu(tr("&Help"));
      helpMenu->addAction(aboutAct);
      helpMenu->addAction(aboutQtAct);
}

void medit::createToolBars()
{
      fileToolBar = addToolBar(tr("File"));
      fileToolBar->addAction(newAct);
      fileToolBar->addAction(openAct);
      fileToolBar->addAction(saveAct);

      editToolBar = addToolBar(tr("Edit"));
      editToolBar->addAction(cutAct);
      editToolBar->addAction(copyAct);
      editToolBar->addAction(pasteAct);
}

void medit::createStatusBar()
{
      statusBar()->showMessage(tr("Ready"));
}

void medit::readSettings()
{
      QSettings settings("Trolltech", "Application Example");
      QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
      QSize size = settings.value("size", QSize(400, 400)).toSize();
      resize(size);
      move(pos);
}

void medit::writeSettings()
{
      QSettings settings("Trolltech", "Application Example");
      settings.setValue("pos", pos());
      settings.setValue("size", size());
}

bool medit::maybeSave()
{
      if (textEdit->document()->isModified()) {
            int ret = QMessageBox::warning(this, tr("Application"),
                        tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
            if (ret == QMessageBox::Yes)
            return save();
            else if (ret == QMessageBox::Cancel)
            return false;
      }
      return true;
}

/*

7-bit MIDI data to 8-bit Alesis data format conversion.
Standard MIDI 0xF0 is removed from beginning, and 0xF7
from the end. Bit conversion as follows:

Original:   Converted:
m1=0abcdefg b1=attttttt  = (m1 And 64)*2 Or m2 
m2=0ttttttt b2=buuuuuuu  = (m1 And 32)*4 Or m3 
m3=0uuuuuuu b3=cvvvvvvv  = (m1 And 16)*8 Or m4 
m4=0vvvvvvv b4=dwwwwwww  = (m1 And 8)*16 Or m5 
m5=0wwwwwww b5=exxxxxxx  = (m1 And 4)*32 Or m6 
m6=0xxxxxxx b6=fyyyyyyy  = (m1 And 2)*64 Or m7 
m7=0yyyyyyy b7=gzzzzzzz  = (m1 And 1)*128 Or m8
m8=0zzzzzzz
*/

QByteArray medit::convertFromSyx(QByteArray patch)
{

unsigned char m[8], b[7];
QByteArray newpatch;
int i=1;

while (i<=patch.size()) {

	for (int j=0;  j <= 7; j++) {
		m[j] = patch[i+j];
	}
	
	b[0] = (m[0] & 64)*2   | m[1];
	b[1] = (m[0] & 32)*4   | m[2];
	b[2] = (m[0] & 16)*8   | m[3];
	b[3] = (m[0] &  8)*16  | m[4];
	b[4] = (m[0] &  4)*32  | m[5];
	b[5] = (m[0] &  2)*64  | m[6];
	b[6] = (m[0] &  1)*128 | m[7];	

	for (int j=0;  j < 7; j++) {
		newpatch.append(b[j]);
	}
	
	i=i+8;
	
}

return newpatch;

}

QByteArray medit::convertToSyx(QByteArray patch)
{

// Convert the binary data used by Medit into the format used by the Micron

}

void medit::loadFile(const QString &fileName)
{
      QFile file(fileName);
      if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Application"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
            return;
      }
	  

// GM: Added binary read
      QApplication::setOverrideCursor(Qt::WaitCursor);
	  QByteArray array = file.readAll();
	  QByteArray patch;
	  QModelIndex parent;

// GM: Code for start and end of sysex patch
      QByteArray startcode;
      startcode.resize(1);
      startcode[0] = 0xf0;
	  startcode[1] = 0x00;
	  startcode[2] = 0x00;
	  startcode[3] = 0x0e;
	  startcode[4] = 0x22;
	  startcode[5] = 0x01;
	  
      QByteArray endcode;
      endcode.resize(1);
      endcode[0] = 0xf7;
	  
	  QByteArray patchname;	

      int counter = 0;
	  int index;
	  
	  treeView->sortByColumn(0);
	  treeView->setFocus();

	  index = array.indexOf(startcode);

// GM: In Model view, use a single top level parent for all the patches		
	  parent = model->index(0, 0, parent);		  
	  
	  while (index!=-1) {

		patch = array.mid(index, array.indexOf(endcode, index)-index);	  
		patch = convertFromSyx(patch);
		
		patchname = patch.mid(OFFSET_NAME, 15);
	
		model->insertRows(0, 1, parent);
 
// GM: Column 1 Patchname		       
		QModelIndex mindex = model->index(0, 0, parent);
		model->setData(mindex, patchname, Qt::EditRole);
		
// GM: Column 2 Type
		mindex = model->index(0, 1, parent);
		switch (patch[OFFSET_CATEGORY]){
			case 0:
				model->setData(mindex, "recent", Qt::EditRole);
				break;
			case 1:
				model->setData(mindex, "faves", Qt::EditRole);
				break;
			case 2:
				model->setData(mindex, "bass", Qt::EditRole);
				break;
			case 3:
				model->setData(mindex, "lead", Qt::EditRole);
				break;
			case 4:
				model->setData(mindex, "pad", Qt::EditRole);
				break;
			case 5:
				model->setData(mindex, "string", Qt::EditRole);
				break;
			case 6:
				model->setData(mindex, "brass", Qt::EditRole);
				break;
			case 7:
				model->setData(mindex, "key", Qt::EditRole);
				break;
			case 8:
				model->setData(mindex, "comp", Qt::EditRole);
				break;
			case 9:
				model->setData(mindex, "drum", Qt::EditRole);
				break;
			case 10:
				model->setData(mindex, "sfx", Qt::EditRole);
				break;
		}
		
// GM: Column 3 Rating
		mindex = model->index(0, 2, parent);
		model->setData(mindex, qVariantFromValue(StarRating(1)));

//GM: Column 3 (Hidden) raw sysex data for patch
        mindex = model->index(0, 3, parent);
		model->setData(mindex, patch);
		
        index = array.indexOf(startcode, ++index);
	
		counter++;
	  }
  
	  file.close();
      QApplication::restoreOverrideCursor();

      setCurrentFile(fileName);
      statusBar()->showMessage(tr("Loaded %1 patches").arg(counter), 4000);
}

QList<QStandardItem*> medit::returnTheItems()
{
        return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

bool medit::saveFile(const QString &fileName)
{
/*      QFile file(fileName);
      if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Application"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
            return false;
      }

      QTextStream out(&file);
      QApplication::setOverrideCursor(Qt::WaitCursor);
      out << textEdit->toPlainText();
      QApplication::restoreOverrideCursor();

      setCurrentFile(fileName); */

	  QList<QStandardItem*> list = returnTheItems();
        
//      foreach (QStandardItem* item, list) {
//              qDebug() << item->data(0,1);
//      }
	  
      statusBar()->showMessage(tr("File saved"), 2000);
      return true;
}

void medit::setCurrentFile(const QString &fileName)
{
      curFile = fileName;
      textEdit->document()->setModified(false);
      setWindowModified(false);

      QString shownName;
      if (curFile.isEmpty())
            shownName = "untitled.txt";
      else
            shownName = strippedName(curFile);

      setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}

QString medit::strippedName(const QString &fullFileName)
{
      return QFileInfo(fullFileName).fileName();
}

medit::~medit()
{

}

