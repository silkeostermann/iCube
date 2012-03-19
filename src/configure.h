#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include "ConfigurationFileHelper.h"
#include <QFile>
#include <QTextStream>
#include "ui_configure.h"


class Configure : public QDialog
{
    Q_OBJECT

	public:
		Configure (QWidget *parent = 0);
		~Configure ();

	public slots:
		void ChangeFile();

	private:

		Ui::ConfigureDialog ui;

		QSpinBox* m_spinbox;
		QComboBox* m_cbo;
};

#endif
