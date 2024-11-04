#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "product.h"
#include <QMessageBox>
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->oui->setModel(product.afficher());



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    // Validate input fields
    if (ui->le_id->text().isEmpty() || ui->le_date->text().isEmpty() ||
        ui->le_montant->text().isEmpty() || ui->le_status->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return; // Exit if any field is empty
    }

    int id = ui->le_id->text().toInt();
    QString date = ui->le_date->text();
    float montant = ui->le_montant->text().toFloat();
    QString status = ui->le_status->text();

    // Create a Product object with the data
    Product product(id, date, montant, status);
    bool test = product.ajouter(); // Call the ajouter function

    if (test)
    {
        QMessageBox::information(this, QObject::tr("Success"),
                    QObject::tr("Addition successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Addition Failed"),
                    QObject::tr("Addition not performed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_sup_clicked()
{

    // Get the ID from the line edit for deletion
    int id = ui->le_sup->text().toInt();

    // Assuming 'e' is the Product object responsible for managing products
    bool test = product.supprimer(id); // Call the supprimer function

    if(test)
    {

        ui->oui->setModel(product.afficher()); // Refresh the table view
        QMessageBox::information(this, QObject::tr("Success"),
                    QObject::tr("Suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Error"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_non_clicked()
{
    // Récupérer l'ID depuis le champ de recherche
    QString productId = ui->le_search->text();

    // Vérifier que l'ID n'est pas vide
    if (productId.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Veuillez entrer un ID de produit valide dans le champ de recherche.");
        return;
    }

    // Récupérer les nouvelles valeurs des champs
    QString newDate = ui->le_date_2->text();
    QString newMontant = ui->le_montant_2->text();
    QString newStatus = ui->le_status_2->text();

    // Vérifier que les champs ne sont pas vides
    if (newDate.isEmpty() || newMontant.isEmpty() || newStatus.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Tous les champs doivent être remplis.");
        return;
    }

    // Préparer la requête pour mettre à jour le produit dans la base de données
    QSqlQuery query;
    query.prepare("UPDATE product SET DATE_COMM = :date, MONTANT_TOTAL = :montant, status = :status WHERE id_pro = :id");
    query.bindValue(":date", newDate);
    query.bindValue(":montant", newMontant);
    query.bindValue(":status", newStatus);
    query.bindValue(":id", productId);

    // Exécuter la requête et vérifier le résultat
    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, "Modification", "Le produit a été modifié avec succès.");
        } else {
            QMessageBox::information(this, "Modification", "Aucun produit trouvé avec cet ID. Vérifiez l'ID.");
        }
    } else {
        // Si la requête échoue
        QMessageBox::critical(this, "Erreur", "Échec de la modification dans la base de données : " + query.lastError().text());
    }
}

void MainWindow::on_search_clicked()
{
    // Récupérer l'ID à partir du champ de recherche
    QString searchTerm = ui->le_search->text();

    // Vérifier que le champ n'est pas vide
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID.");
        return;
    }

    // Préparer la requête SQL pour rechercher le produit
    QSqlQuery query;
    query.prepare("SELECT DATE_COMM, MONTANT_TOTAL, STATUS FROM product WHERE id_pro = :id");
    query.bindValue(":id", searchTerm);

    // Exécuter la requête et traiter les résultats
    if (query.exec()) {
        if (query.next()) {
            // Si le produit est trouvé, remplir les champs
            QString date = query.value(0).toString();
            QString montant = query.value(1).toString();
            QString status = query.value(2).toString();

            ui->le_date_2->setText(date);
            ui->le_montant_2->setText(montant);
            ui->le_status_2->setText(status);
        } else {
            // Si aucun produit n'est trouvé avec cet ID
            QMessageBox::information(this, "Recherche", "Aucun produit trouvé avec cet ID.");
        }
    } else {
        // Si la requête échoue
        QMessageBox::critical(this, "Erreur", "Échec de la recherche dans la base de données : " + query.lastError().text());
    }
}

void MainWindow::searchProducts(const QString &searchTerm) {
    // Call the search method from Product
    QSqlQueryModel *model = product.modifier(searchTerm);
    if (model && model->rowCount() > 0) { // Check if the model was created and has results
        ui->oui->setModel(model); // Update the table view with the search results
    } else {
        QMessageBox::warning(this, "Search Error", "No products found matching your search.");
        ui->oui->setModel(nullptr); // Clear the table view if no results found
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    ui->oui->setModel(product.afficher());
}

