#include "MainGui.h"
#include "qlayout.h"
#include "qlist.h"


MainGui::MainGui(QWidget *parent)
    : QMainWindow(parent)
{
    caisse_ = new Caisse;
    caisseIsLocal_ = true;
    ui.setupUi(this);
    setUp();
}

MainGui::MainGui(Caisse* caisse, QWidget* parent ) : QMainWindow(parent)
{
    caisse_ = caisse;
    caisseIsLocal_ = false;
    ui.setupUi(this);
    setUp();

}

MainGui::~MainGui()
{
    if (caisseIsLocal_) 
    {
        delete caisse_;
    }
}

void MainGui::setUp()
{
    setMenu();
    setUi();

    QObject::connect(caisse_, &Caisse::articleAjoute, this, &MainGui::ajouterListWidgetItem);
    QObject::connect(caisse_, &Caisse::articleRetire, this, &MainGui::retireListWidgetITem);
}

void MainGui::update() {
    caisse_->calculerTotalAvantTaxe();
    caisse_->calculTotalDesTaxes();
    totalAvantTaxes_->setText("total avant taxes = " + QString::fromStdString(caisse_->getTotalAvTaxe()));
    totalDesTaxes_->setText("total des taxes = " + QString::fromStdString(caisse_->getTotalDesTaxes()));
    totalAPayer_->setText("total a payer = " + QString::fromStdString(caisse_->getTotal()));
}

void MainGui::controlRetirerArticle() {
    
    QList<QListWidgetItem*> list = affichage_->selectedItems();
    
    if (list.isEmpty())
        return;


    std::string description = ((list[0]->data(Qt::UserRole)).toString()).toStdString();
    caisse_->retirerArticle(description);
    
    int size = caisse_->articleAjoutes.size();
    
    if (size == 0)
        retirer_->setDisabled(true);
}

void MainGui::retireListWidgetITem() {
    QList<QListWidgetItem*> list = affichage_->selectedItems();

    if (list.isEmpty())
        return;

    delete list[0];

    if (caisse_->articleAjoutes.size() == 0) {
        reinitialiser_->setDisabled(true);
        retirer_->setDisabled(true);
    }

    update();

}


void MainGui::controlAjouterArticle() 
{
    std::string descrition = (descriptionLineEdit_->text()).toStdString();
    double prix = (prixLineEdit_->text()).toDouble();
    
    Caisse::Article* article = new Caisse::Article{ descrition, prix, taxableOption_->isChecked() };
    caisse_->ajouterArticle(*article);

    retirer_->setDisabled(false);
    reinitialiser_->setDisabled(false);
    descriptionLineEdit_->clear();
    prixLineEdit_->clear();
    taxableOption_->setChecked(false);

    delete article;
}

void MainGui::controlReinitialiser() {
    caisse_->reinitialiser();
    affichage_->clear();
    retirer_->setDisabled(true);
    reinitialiser_->setDisabled(true);

    update();

}

void MainGui::ajouterListWidgetItem() {
    
    Caisse::Article article = (caisse_->articleAjoutes)[caisse_->articleAjoutes.size() - 1];
    QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(article.formatage()));
    
    affichage_->addItem(item);
    std::string description = caisse_->articleAjoutes[((caisse_->articleAjoutes).size() - 1)].description;
    item->setData(Qt::UserRole, QString::fromStdString(description));

    update();
}


void MainGui::setMenu() {
    // On crée un bouton 'Exit'
    QAction* exit = new QAction(tr("E&xit"), this);
    // On ajoute un raccourci clavier qui simulera l'appui sur ce bouton (Ctrl+Q)
    exit->setShortcuts(QKeySequence::Quit);
    // On connecte le clic sur ce bouton avec l'action de clore le programme
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    // On crée un nouveau menu 'File'
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    // Dans lequel on ajoute notre bouton 'Exit'
    fileMenu->addAction(exit);
}

void MainGui::setUi() 
{
    // creation des QlineEdit
    descriptionLineEdit_ = new QLineEdit(this);
    QLabel* descriptionLabel = new QLabel(this);
    descriptionLabel->setText("description:");
    QHBoxLayout* DescriptionBox = new QHBoxLayout(this);
    DescriptionBox->addWidget(descriptionLabel);
    DescriptionBox->addWidget(descriptionLineEdit_);

    
    prixLineEdit_ = new QLineEdit(this);
    QLabel* prixLabel = new QLabel(this);
    QHBoxLayout* prixBox = new QHBoxLayout(this);
    prixLabel->setText("prix:");
    prixBox->addWidget(prixLabel);
    prixBox->addWidget(prixLineEdit_);
    
    
    

    //creation des Push Button
    ajouter_ = new QPushButton(this);
    ajouter_->setText("ajouter article");
    connect(ajouter_,SIGNAL(clicked()), this, SLOT(controlAjouterArticle()));

    retirer_ = new QPushButton(this);
    retirer_->setText("retirer article");
    retirer_->setDisabled(true);
    connect(retirer_, SIGNAL(clicked()), this, SLOT(controlRetirerArticle()));

    reinitialiser_ = new QPushButton(this);
    reinitialiser_->setText("reinitialiser");
    reinitialiser_->setDisabled(true);
    connect(reinitialiser_, &QPushButton::clicked, this, &MainGui::controlReinitialiser);

    //creation du check box
    taxableOption_ = new QCheckBox(this);
    taxableOption_->setText("taxable");

    //creation du Liste Widget
    affichage_ = new QListWidget(this);
    
    // just a frame
    QFrame* frame = new QFrame(this);
    frame->setFrameShape(QFrame::HLine);

    //Creation des labels
    
    totalAvantTaxes_ = new QLabel(this);
    totalAvantTaxes_->setText("total avant taxes = 0.00" );
    
    totalDesTaxes_ = new QLabel(this);
    totalDesTaxes_->setText("total des taxes = 0.00");

    totalAPayer_ = new QLabel(this);
    totalAPayer_->setText("total a payer = 0.00");

    //
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(DescriptionBox);
    mainLayout->addLayout(prixBox);
    mainLayout->addWidget(taxableOption_);
    mainLayout->addWidget(ajouter_);
    mainLayout->addWidget(retirer_);
    mainLayout->addWidget(reinitialiser_);
    mainLayout->addWidget(affichage_);
    mainLayout->addWidget(frame);
    mainLayout->addWidget(totalAvantTaxes_);
    mainLayout->addWidget(totalDesTaxes_);
    mainLayout->addWidget(totalAPayer_);

    QWidget* mainWidget = new QWidget(this);
   
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    std::string title = "polyCaisse";
    setWindowTitle(title.c_str());
}