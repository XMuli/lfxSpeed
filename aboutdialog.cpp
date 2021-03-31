/*
 * Copyright (c) 2020 xmuli
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 * GitHub:  https://github.com/xmuli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * */

#include "aboutdialog.h"

#include <QWidget>
#include <QLayout>
#include <QDebug>
#include <DLabel>

DWIDGET_USE_NAMESPACE

AboutDialog::AboutDialog(QWidget *parent)
    : DDialog(parent)
{
    init();
}

void AboutDialog::init()
{
    setTitle(tr("lfxSpeed"));
    setMessage(tr("A light and fast network speed plugin(DDE)."));

    QVBoxLayout* mainLayout = static_cast<QVBoxLayout *>(layout());
    DLabel *labLogo = new DLabel();
    labLogo->setPixmap(QPixmap(":/images/lfxSpeed.svg"));
    labLogo->resize(200, 200);
    mainLayout->insertWidget(1, labLogo, 0, Qt::AlignCenter);

    QWidget *content = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout(content);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->addSpacing(15);
    DLabel *labVersion = new DLabel(tr("Version: 0.6.5  2021/03/31"));
    DLabel *labCopyright = new DLabel(tr("Copyright (c) 2021 By ifmet.cn"));
    vLayout->addWidget(labVersion, 0, Qt::AlignCenter);
    vLayout->addWidget(labCopyright, 0, Qt::AlignCenter);
    vLayout->addSpacing(15);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    DLabel *labAuthor = new DLabel();
    labAuthor->setOpenExternalLinks(true);
    labAuthor->setText(tr("<a href=\"https://ifmet.cn\">Author"));
    DLabel *labGithub = new DLabel();
    labGithub->setOpenExternalLinks(true);
    labGithub->setText(tr("<a href=\"https://github.com/xmuli/lfxSpeed\">GitHub"));
    DLabel *labLicense = new DLabel();
    labLicense->setOpenExternalLinks(true);
    labLicense->setText(tr("<a href=\"https://github.com/xmuli/lfxSpeed/blob/master/LICENSE\">License"));
    DLabel *labDonation = new DLabel();
    labDonation->setOpenExternalLinks(true);
    labDonation->setText(tr("<a href=\"\">Donation"));
    DLabel *labAcknowledgements = new DLabel();
    labAcknowledgements->setOpenExternalLinks(true);
    labAcknowledgements->setText(tr("<a href=\"https://github.com/justforlxz\">Author"));
    hLayout->addWidget(labAuthor);
    hLayout->addWidget(labGithub);
    hLayout->addWidget(labLicense);
    hLayout->addWidget(labAcknowledgements);

    vLayout->addLayout(hLayout);
    addContent(content);
}
