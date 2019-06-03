SET storage_engine=InnoDB;
SET FOREIGN_KEY_CHECKS=1;
CREATE DATABASE IF NOT EXISTS market;

use market;

DROP TABLE IF EXISTS product;
DROP TABLE IF EXISTS carrello;

CREATE TABLE product (
    id INT,
    nome CHAR(50) NOT NULL,
    prezzo FLOAT NOT NULL,
    descrizione CHAR(200) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE carrello (
    id INT,
    qnt INT NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (id) 
        REFERENCES product(id) 
        ON DELETE CASCADE 
        ON UPDATE CASCADE
);

INSERT INTO product (id, nome,prezzo,descrizione)
VALUES (111, 'Samsung Monitor Curvo', 129.99,'Avvolgendo il campo visivo come in un cinema iMax, lo schermo curvo amplia il campo visivo incrementando la percezione di profondità.');
INSERT INTO product (id, nome,prezzo,descrizione)
VALUES (112, 'Logitech Tastiera Gaming', 66.16,'Grazie ai tasti ottimizzati per videogiochi e le prestazioni di illuminazione e comfort, consente un gioco più veloce rispetto alle tastiere standard.');
INSERT INTO product (id, nome,prezzo,descrizione)
VALUES (113, 'Logitech Mouse Hyperion Fury', 39.99,'Con una frequenza di aggiornamento di 1 ms puoi essere certo che tutta la precisione e rapidità delle tue mosse verrà trasmessa al gioco con la velocità.');
INSERT INTO product (id, nome,prezzo,descrizione)
VALUES (114, 'AUKEY Tappetino Mouse', 17.99,'Interazione precisa con sensore ottico su tutto il pad, il bordo intrecciato significa che non danneggia o irritera i tuoi polsi.');
INSERT INTO product (id, nome,prezzo,descrizione)
VALUES (115, 'HyperX Cloud Alpha Cuffie', 73.99,'Ll rivoluzionario design dei driver a doppia camera delle cuffie HyperX Cloud Alpha regala un audio chiaro e limpido.');
INSERT INTO product (id, nome,prezzo,descrizione)
VALUES (116, 'Razer Gaming Controller ', 129.99,'Disposizione ergonomica dei pulsanti multifunzione per un controllo ottimale.');
INSERT INTO product (id, nome,prezzo,descrizione)
VALUES (117, 'Diablo X-One Gaming Sedia', 144.99,'Sedia da ufficio dal design sportivo da corsa, dalla forma ergonomica, Lavorazione di alta qualità, perfetta per ufficio e casa.');
