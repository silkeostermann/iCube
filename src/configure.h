#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>
#include "ui_configure.h"


class Configure : public QDialog
{
    Q_OBJECT

	public:
		Configure(QWidget *parent = 0);
		~Configure();

	public slots:

	private:

		Ui::ConfigureDialog ui;
};

#endif
