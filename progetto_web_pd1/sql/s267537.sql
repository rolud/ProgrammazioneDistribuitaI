-- phpMyAdmin SQL Dump
-- version 4.5.4.1deb2ubuntu2.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Creato il: Giu 17, 2019 alle 14:04
-- Versione del server: 5.7.26-0ubuntu0.16.04.1
-- Versione PHP: 7.0.33-0ubuntu0.16.04.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `s267537`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `Seats`
--

DROP TABLE IF EXISTS `Seats`;
CREATE TABLE `Seats` (
  `id` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `usr` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `stat` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `Seats`
--

INSERT INTO `Seats` (`id`, `usr`, `stat`) VALUES
('A4', 'u1@p.it', 1),
('B2', 'u2@p.it', 2),
('B3', 'u2@p.it', 2),
('B4', 'u2@p.it', 2),
('D4', 'u1@p.it', 1),
('F4', 'u2@p.it', 1);

-- --------------------------------------------------------

--
-- Struttura della tabella `Users`
--

DROP TABLE IF EXISTS `Users`;
CREATE TABLE `Users` (
  `usr` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `pwd` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `sale` varchar(10) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `Users`
--

INSERT INTO `Users` (`usr`, `pwd`, `sale`) VALUES
('u1@p.it', '89e0d2d19cd6feeb269110bcc28995e3', 'nmbzhm0T0A'),
('u2@p.it', 'e51a62d94313cac44792d88ad5ba20a6', 'wFGSi4NHZB');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `Seats`
--
ALTER TABLE `Seats`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `Users`
--
ALTER TABLE `Users`
  ADD PRIMARY KEY (`usr`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
