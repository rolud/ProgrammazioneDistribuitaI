-- phpMyAdmin SQL Dump
-- version 4.5.4.1deb2ubuntu2.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 10, 2019 at 06:32 PM
-- Server version: 5.7.26-0ubuntu0.16.04.1
-- PHP Version: 7.0.33-0ubuntu0.16.04.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `masala`
--

-- --------------------------------------------------------

--
-- Table structure for table `books`
--

CREATE TABLE `books` (
  `Title` varchar(54) DEFAULT NULL,
  `Author` varchar(22) DEFAULT NULL,
  `Genre` varchar(10) DEFAULT NULL,
  `Subgenre` varchar(17) DEFAULT NULL,
  `Price` varchar(6) DEFAULT NULL,
  `Publisher` varchar(16) DEFAULT NULL,
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `books`
--

INSERT INTO `books` (`Title`, `Author`, `Genre`, `Subgenre`, `Price`, `Publisher`, `id`) VALUES
('Fundamentals of Wavelets', 'Goswami, Jaideva', 'tech', 'signal_processing', '228', 'Wiley', 1),
('Data Smart', 'Foreman, John', 'tech', 'data_science', '235', 'Wiley', 2),
('God Created the Integers', 'Hawking, Stephen', 'tech', 'mathematics', '197', 'Penguin', 3),
('Superfreakonomics', 'Dubner, Stephen', 'science', 'economics', '179', 'HarperCollins', 4),
('Orientalism', 'Said, Edward', 'nonfiction', 'history', '197', 'Penguin', 5),
('Nature of Statistical Learning Theory, The', 'Vapnik, Vladimir', 'tech', 'data_science', '230', 'Springer', 6),
('Integration of the Indian States', 'Menon, V P', 'nonfiction', 'history', '217', 'Orient Blackswan', 7),
('Drunkard\'s Walk, The', 'Mlodinow, Leonard', 'science', 'mathematics', '197', 'Penguin', 8),
('Image Processing & Mathematical Morphology', 'Shih, Frank', 'tech', 'signal_processing', '241', 'CRC', 9),
('How to Think Like Sherlock Holmes', 'Konnikova, Maria', 'nonfiction', 'psychology', '240', 'Penguin', 10),
('Data Scientists at Work', 'Sebastian Gutierrez', 'tech', 'data_science', '230', 'Apress', 11),
('Slaughterhouse Five', 'Vonnegut, Kurt', 'fiction', 'classic', '198', 'Random House', 12),
('Birth of a Theorem', 'Villani, Cedric', 'science', 'mathematics', '234', 'Bodley Head', 13),
('Structure & Interpretation of Computer Programs', 'Sussman, Gerald', 'tech', 'computer_science', '240', 'MIT Press', 14),
('Age of Wrath, The', 'Eraly, Abraham', 'nonfiction', 'history', '238', 'Penguin', 15),
('Trial, The', 'Kafka, Frank', 'fiction', 'classic', '198', 'Random House', 16),
('Statistical Decision Theory\'', 'Pratt, John', 'tech', 'data_science', '236', 'MIT Press', 17),
('Data Mining Handbook', 'Nisbet, Robert', 'tech', 'data_science', '242', 'Apress', 18),
('New Machiavelli, The', 'Wells, H. G.', 'fiction', 'novel', '180', 'Penguin', 19),
('Physics & Philosophy', 'Heisenberg, Werner', 'philosophy', 'science', '197', 'Penguin', 20),
('Making Software', 'Oram, Andy', 'tech', 'computer_science', '232', 'O\'Reilly', 21),
('Analysis, Vol I', 'Tao, Terence', 'tech', 'mathematics', '248', 'HBA', 22),
('Machine Learning for Hackers', 'Conway, Drew', 'tech', 'data_science', '233', 'O\'Reilly', 23),
('Signal and the Noise, The', 'Silver, Nate', 'tech', 'data_science', '233', 'Penguin', 24),
('Python for Data Analysis', 'McKinney, Wes', 'tech', 'data_science', '233', 'O\'Reilly', 25),
('Introduction to Algorithms', 'Cormen, Thomas', 'tech', 'computer_science', '234', 'MIT Press', 26),
('Beautiful and the Damned, The', 'Deb, Siddhartha', 'nonfiction', 'history', '198', 'Penguin', 27),
('Outsider, The', 'Camus, Albert', 'fiction', 'classic', '198', 'Penguin', 28),
('Complete Sherlock Holmes, The - Vol I', 'Doyle, Arthur Conan', 'fiction', 'classic', '176', 'Random House', 29),
('Complete Sherlock Holmes, The - Vol II', 'Doyle, Arthur Conan', 'fiction', 'classic', '176', 'Random House', 30),
('Wealth of Nations, The', 'Smith, Adam', 'science', 'economics', '175', 'Random House', 31),
('Pillars of the Earth, The', 'Follett, Ken', 'fiction', 'novel', '176', 'Random House', 32),
('Mein Kampf', 'Hitler, Adolf', 'nonfiction', 'autobiography', '212', 'Rupa', 33),
('Tao of Physics, The', 'Capra, Fritjof', 'science', 'physics', '179', 'Penguin', 34),
('Surely You\'re Joking Mr Feynman', 'Feynman, Richard', 'science', 'physics', '198', 'Random House', 35),
('Farewell to Arms, A', 'Hemingway, Ernest', 'fiction', 'classic', '179', 'Rupa', 36),
('Veteran, The', 'Forsyth, Frederick', 'fiction', 'novel', '177', 'Transworld', 37),
('False Impressions', 'Archer, Jeffery', 'fiction', 'novel', '177', 'Pan', 38),
('Last Lecture, The', 'Pausch, Randy', 'nonfiction', 'autobiography', '197', 'Hyperion', 39),
('Return of the Primitive', 'Rand, Ayn', 'philosophy', 'objectivism', '202', 'Penguin', 40),
('Jurassic Park', 'Crichton, Michael', 'fiction', 'novel', '174', 'Random House', 41),
('Russian Journal, A', 'Steinbeck, John', 'nonfiction', 'history', '196', 'Penguin', 42),
('Tales of Mystery and Imagination', 'Poe, Edgar Allen', 'fiction', 'classic', '172', 'HarperCollins', 43),
('Freakonomics', 'Dubner, Stephen', 'science', 'economics', '197', 'Penguin', 44),
('Hidden Connections, The', 'Capra, Fritjof', 'science', 'physics', '197', 'HarperCollins', 45),
('Story of Philosophy, The', 'Durant, Will', 'philosophy', 'history', '170', 'Pocket', 46),
('Asami Asami', 'Deshpande, P L', 'fiction', 'novel', '205', 'Mauj', 47),
('Journal of a Novel', 'Steinbeck, John', 'fiction', 'classic', '196', 'Penguin', 48),
('Once There Was a War', 'Steinbeck, John', 'nonfiction', 'history', '196', 'Penguin', 49),
('Moon is Down, The', 'Steinbeck, John', 'fiction', 'classic', '196', 'Penguin', 50),
('Brethren, The', 'Grisham, John', 'fiction', 'novel', '174', 'Random House', 51),
('In a Free State', 'Naipaul, V. S.', 'fiction', 'novel', '196', 'Rupa', 52),
('Catch 22', 'Heller, Joseph', 'fiction', 'classic', '178', 'Random House', 53),
('Complete Mastermind, The', 'BBC', 'nonfiction', 'trivia', '178', 'BBC', 54),
('Dylan on Dylan', 'Dylan, Bob', 'nonfiction', 'autobiography', '197', 'Random House', 55),
('Soft Computing & Intelligent Systems', 'Gupta, Madan', 'tech', 'data_science', '242', 'Elsevier', 56),
('Textbook of Economic Theory', 'Stonier, Alfred', 'tech', 'economics', '242', 'Pearson', 57),
('Econometric Analysis', 'Greene, W. H.', 'tech', 'economics', '242', 'Pearson', 58),
('Learning OpenCV', 'Bradsky, Gary', 'tech', 'signal_processing', '232', 'O\'Reilly', 59),
('Data Structures Using C & C++', 'Tanenbaum, Andrew', 'tech', 'computer_science', '235', 'Prentice Hall', 60),
('Computer Vision, A Modern Approach', 'Forsyth, David', 'tech', 'signal_processing', '255', 'Pearson', 61),
('Principles of Communication Systems', 'Taub, Schilling', 'tech', 'signal_processing', '240', 'TMH', 62),
('Let Us C', 'Kanetkar, Yashwant', 'tech', 'computer_science', '213', 'Prentice Hall', 63),
('Amulet of Samarkand, The', 'Stroud, Jonathan', 'fiction', 'novel', '179', 'Random House', 64),
('Crime and Punishment', 'Dostoevsky, Fyodor', 'fiction', 'classic', '180', 'Penguin', 65),
('Angels & Demons', 'Brown, Dan', 'fiction', 'novel', '178', 'Random House', 66),
('Argumentative Indian, The', 'Sen, Amartya', 'nonfiction', 'history', '209', 'Picador', 67),
('Sea of Poppies', 'Ghosh, Amitav', 'fiction', 'novel', '197', 'Penguin', 68),
('Idea of Justice, The', 'Sen, Amartya', 'philosophy', 'economics', '212', 'Penguin', 69),
('Raisin in the Sun, A', 'Hansberry, Lorraine', 'fiction', 'novel', '175', 'Penguin', 70),
('All the President\'s Men', 'Woodward, Bob', 'nonfiction', 'history', '177', 'Random House', 71),
('Prisoner of Birth, A', 'Archer, Jeffery', 'fiction', 'novel', '176', 'Pan', 72),
('Scoop!', 'Nayar, Kuldip', 'nonfiction', 'history', '216', 'HarperCollins', 73),
('Ahe Manohar Tari', 'Deshpande, Sunita', 'nonfiction', 'autobiography', '213', 'Mauj', 74),
('Last Mughal, The', 'Dalrymple, William', 'nonfiction', 'history', '199', 'Penguin', 75),
('Social Choice & Welfare, Vol 39 No. 1', 'Various', 'tech', 'economics', '235', 'Springer', 76),
('Radiowaril Bhashane & Shrutika', 'Deshpande, P L', 'nonfiction', 'misc', '213', 'Mauj', 77),
('Gun Gayin Awadi', 'Deshpande, P L', 'nonfiction', 'misc', '212', 'Mauj', 78),
('Aghal Paghal', 'Deshpande, P L', 'nonfiction', 'misc', '212', 'Mauj', 79),
('Maqta-e-Ghalib', 'Garg, Sanjay', 'nonfiction', 'poetry', '221', 'Mauj', 80),
('Beyond Degrees', '', 'philosophy', 'education', '222', 'HarperCollins', 81),
('Manasa', 'Kale, V P', 'nonfiction', 'misc', '213', 'Mauj', 82),
('India from Midnight to Milennium', 'Tharoor, Shashi', 'nonfiction', 'history', '198', 'Penguin', 83),
('World\'s Greatest Trials, The', '', 'nonfiction', 'history', '210', '', 84),
('Great Indian Novel, The', 'Tharoor, Shashi', 'fiction', 'novel', '198', 'Penguin', 85),
('O Jerusalem!', 'Lapierre, Dominique', 'nonfiction', 'history', '217', 'vikas', 86),
('City of Joy, The', 'Lapierre, Dominique', 'fiction', 'novel', '177', 'vikas', 87),
('Freedom at Midnight', 'Lapierre, Dominique', 'nonfiction', 'history', '167', 'vikas', 88),
('Winter of Our Discontent, The', 'Steinbeck, John', 'fiction', 'classic', '196', 'Penguin', 89),
('On Education', 'Russell, Bertrand', 'philosophy', 'education', '203', 'Routledge', 90),
('Free Will', 'Harris, Sam', 'nonfiction', 'psychology', '203', 'FreePress', 91),
('Bookless in Baghdad', 'Tharoor, Shashi', 'nonfiction', 'history', '206', 'Penguin', 92),
('Case of the Lame Canary, The', 'Gardner, Earle Stanley', 'fiction', 'novel', '179', '', 93),
('Theory of Everything, The', 'Hawking, Stephen', 'science', 'physics', '217', 'Jaico', 94),
('New Markets & Other Essays', 'Drucker, Peter', 'science', 'economics', '176', 'Penguin', 95),
('Electric Universe', 'Bodanis, David', 'science', 'physics', '201', 'Penguin', 96),
('Hunchback of Notre Dame, The', 'Hugo, Victor', 'fiction', 'classic', '175', 'Random House', 97),
('Burning Bright', 'Steinbeck, John', 'fiction', 'classic', '175', 'Penguin', 98),
('Age of Discontuinity, The', 'Drucker, Peter', 'nonfiction', 'economics', '178', 'Random House', 99),
('Doctor in the Nude', 'Gordon, Richard', 'fiction', 'novel', '179', 'Penguin', 100),
('Down and Out in Paris & London', 'Orwell, George', 'nonfiction', 'autobiography', '179', 'Penguin', 101),
('Identity & Violence', 'Sen, Amartya', 'philosophy', 'philosophy', '219', 'Penguin', 102),
('Beyond the Three Seas', 'Dalrymple, William', 'nonfiction', 'history', '197', 'Random House', 103),
('World\'s Greatest Short Stories, The', '', 'fiction', 'classic', '217', 'Jaico', 104),
('Talking Straight', 'Iacoca, Lee', 'nonfiction', 'autobiography', '175', '', 105),
('Maugham\'s Collected Short Stories, Vol 3', 'Maugham, William S', 'fiction', 'classic', '171', 'Vintage', 106),
('Phantom of Manhattan, The', 'Forsyth, Frederick', 'fiction', 'classic', '180', '', 107),
('Ashenden of The British Agent', 'Maugham, William S', 'fiction', 'classic', '160', 'Vintage', 108),
('Zen & The Art of Motorcycle Maintenance', 'Pirsig, Robert', 'philosophy', 'autobiography', '172', 'Vintage', 109),
('Great War for Civilization, The', 'Fisk, Robert', 'nonfiction', 'history', '197', 'HarperCollins', 110),
('We the Living', 'Rand, Ayn', 'fiction', 'novel', '178', 'Penguin', 111),
('Artist and the Mathematician, The', 'Aczel, Amir', 'science', 'mathematics', '186', 'HighStakes', 112),
('History of Western Philosophy', 'Russell, Bertrand', 'philosophy', 'philosophy', '213', 'Routledge', 113),
('Selected Short Stories', '', 'fiction', 'classic', '215', 'Jaico', 114),
('Rationality & Freedom', 'Sen, Amartya', 'science', 'economics', '213', 'Springer', 115),
('Clash of Civilizations and Remaking of the World Order', 'Huntington, Samuel', 'nonfiction', 'history', '228', 'Simon&Schuster', 116),
('Uncommon Wisdom', 'Capra, Fritjof', 'nonfiction', 'anthology', '197', 'Fontana', 117),
('One', 'Bach, Richard', 'nonfiction', 'autobiography', '172', 'Dell', 118),
('Karl Marx Biography', '', 'nonfiction', 'autobiography', '162', '', 119),
('To Sir With Love', 'Braithwaite', 'fiction', 'classic', '197', 'Penguin', 120),
('Half A Life', 'Naipaul, V S', 'fiction', 'novel', '196', '', 121),
('Discovery of India, The', 'Nehru, Jawaharlal', 'nonfiction', 'history', '230', '', 122),
('Apulki', 'Deshpande, P L', 'nonfiction', 'misc', '211', '', 123),
('Unpopular Essays', 'Russell, Bertrand', 'philosophy', 'philosophy', '198', '', 124),
('Deceiver, The', 'Forsyth, Frederick', 'fiction', 'novel', '178', '', 125),
('Veil: Secret Wars of the CIA', 'Woodward, Bob', 'nonfiction', 'history', '171', '', 126),
('Char Shabda', 'Deshpande, P L', 'nonfiction', 'misc', '214', '', 127),
('Rosy is My Relative', 'Durrell, Gerald', 'fiction', 'novel', '176', '', 128),
('Moon and Sixpence, The', 'Maugham, William S', 'fiction', 'classic', '180', '', 129),
('Political Philosophers', '', 'philosophy', 'politics', '162', '', 130),
('Short History of the World, A', 'Wells, H G', 'nonfiction', 'history', '197', '', 131),
('Trembling of a Leaf, The', 'Maugham, William S', 'fiction', 'novel', '205', '', 132),
('Doctor on the Brain', 'Gordon, Richard', 'fiction', 'novel', '204', '', 133),
('Simpsons & Their Mathematical Secrets', 'Singh, Simon', 'science', 'mathematics', '233', '', 134),
('Pattern Classification', 'Duda, Hart', 'tech', 'data_science', '241', '', 135),
('From Beirut to Jerusalem', 'Friedman, Thomas', 'nonfiction', 'history', '202', '', 136),
('Code Book, The', 'Singh, Simon', 'science', 'mathematics', '197', '', 137),
('Age of the Warrior, The', 'Fisk, Robert', 'nonfiction', 'history', '197', '', 138),
('Final Crisis', '', 'fiction', 'comic', '257', '', 139),
('Killing Joke, The', '', 'fiction', 'comic', '283', '', 140),
('Flashpoint', '', 'fiction', 'comic', '265', '', 141),
('Batman Earth One', '', 'fiction', 'comic', '265', '', 142),
('Crisis on Infinite Earths', '', 'fiction', 'comic', '258', '', 143),
('Numbers Behind Numb3rs, The', 'Devlin, Keith', 'science', 'mathematics', '202', '', 144),
('Superman Earth One - 1', '', 'fiction', 'comic', '259', '', 145),
('Superman Earth One - 2', '', 'fiction', 'comic', '258', '', 146),
('Justice League: Throne of Atlantis', '', 'fiction', 'comic', '258', '', 147),
('Justice League: The Villain\'s Journey', '', 'fiction', 'comic', '258', '', 148),
('Death of Superman, The', '', 'fiction', 'comic', '258', '', 149),
('History of the DC Universe', '', 'fiction', 'comic', '258', '', 150),
('Batman: The Long Halloween', '', 'fiction', 'comic', '258', '', 151),
('Life in Letters, A', 'Steinbeck, John', 'nonfiction', 'autobiography', '196', '', 152),
('Information, The', 'Gleick, James', 'science', 'mathematics', '233', '', 153),
('Journal of Economics, vol 106 No 3', '', 'science', 'economics', '235', '', 154),
('Elements of Information Theory', 'Thomas, Joy', 'tech', 'signal_processing', '229', '', 155),
('Power Electronics - Rashid', 'Rashid, Muhammad', 'tech', 'computer_science', '235', '', 156),
('Power Electronics - Mohan', 'Mohan, Ned', 'tech', 'computer_science', '237', '', 157),
('Neural Networks', 'Haykin, Simon', 'tech', 'data_science', '240', '', 158),
('Grapes of Wrath, The', 'Steinbeck, John', 'fiction', 'classic', '196', '', 159),
('Vyakti ani Valli', 'Deshpande, P L', 'nonfiction', 'misc', '211', '', 160),
('Statistical Learning Theory', 'Vapnik, Vladimir', 'tech', 'data_science', '228', '', 161),
('Empire of the Mughal - The Tainted Throne', 'Rutherford, Alex', 'nonfiction', 'history', '180', '', 162),
('Empire of the Mughal - Brothers at War', 'Rutherford, Alex', 'nonfiction', 'history', '180', '', 163),
('Empire of the Mughal - Ruler of the World', 'Rutherford, Alex', 'nonfiction', 'history', '180', '', 164),
('Empire of the Mughal - The Serpent\'s Tooth', 'Rutherford, Alex', 'nonfiction', 'history', '180', '', 165),
('Empire of the Mughal - Raiders from the North', 'Rutherford, Alex', 'nonfiction', 'history', '180', '', 166),
('Mossad', 'Baz-Zohar, Michael', 'nonfiction', 'history', '236', '', 167),
('Jim Corbett Omnibus', 'Corbett, Jim', 'nonfiction', 'history', '223', '', 168),
('20000 Leagues Under the Sea', 'Verne, Jules', 'fiction', 'novel', '190', '', 169),
('Batatyachi Chal', 'Deshpande P L', 'fiction', 'novel', '200', '', 170),
('Hafasavnuk', 'Deshpande P L', 'fiction', 'novel', '211', '', 171),
('Urlasurla', 'Deshpande P L', 'fiction', 'novel', '211', '', 172),
('Pointers in C', 'Kanetkar, Yashwant', 'tech', 'computer_science', '213', '', 173),
('Cathedral and the Bazaar, The', 'Raymond, Eric', 'tech', 'computer_science', '217', '', 174),
('Design with OpAmps', 'Franco, Sergio', 'tech', 'computer_science', '240', '', 175),
('Think Complexity', 'Downey, Allen', 'tech', 'data_science', '230', '', 176),
('Devil\'s Advocate, The', 'West, Morris', 'fiction', 'novel', '178', '', 177),
('Ayn Rand Answers', 'Rand, Ayn', 'philosophy', 'objectivism', '203', '', 178),
('Philosophy: Who Needs It', 'Rand, Ayn', 'philosophy', 'objectivism', '171', '', 179),
('World\'s Great Thinkers, The', '', 'science', 'physics', '189', '', 180),
('Data Analysis with Open Source Tools', 'Janert, Phillip', 'tech', 'data_science', '230', '', 181),
('Broca\'s Brain', 'Sagan, Carl', 'science', 'physics', '174', '', 182),
('Men of Mathematics', 'Bell, E T', 'science', 'mathematics', '217', '', 183),
('Oxford book of Modern Science Writing', 'Dawkins, Richard', 'science', 'science', '240', '', 184),
('Justice, Judiciary and Democracy', 'Ranjan, Sudhanshu', 'nonfiction', 'legal', '224', '', 185),
('Arthashastra, The', 'Kautiyla', 'philosophy', 'philosophy', '214', '', 186),
('We the People', 'Palkhivala', 'philosophy', 'philosophy', '216', '', 187),
('We the Nation', 'Palkhivala', 'philosophy', 'philosophy', '216', '', 188),
('Courtroom Genius, The', 'Sorabjee', 'nonfiction', 'autobiography', '217', '', 189),
('Dongri to Dubai', 'Zaidi, Hussain', 'nonfiction', 'history', '216', '', 190),
('History of England, Foundation', 'Ackroyd, Peter', 'nonfiction', 'history', '197', '', 191),
('City of Djinns', 'Dalrymple, William', 'nonfiction', 'history', '198', '', 192),
('India\'s Legal System', 'Nariman', 'nonfiction', 'legal', '177', '', 193),
('More Tears to Cry', 'Sassoon, Jean', 'fiction', 'novel', '235', '', 194),
('Ropemaker, The', 'Dickinson, Peter', 'fiction', 'novel', '196', '', 195),
('Angels & Demons', 'Brown, Dan', 'fiction', 'novel', '170', '', 196),
('Judge, The', '', 'fiction', 'novel', '170', '', 197),
('Attorney, The', '', 'fiction', 'novel', '170', '', 198),
('Prince, The', 'Machiavelli', 'fiction', 'classic', '173', '', 199),
('Eyeless in Gaza', 'Huxley, Aldous', 'fiction', 'novel', '180', '', 200),
('Tales of Beedle the Bard', 'Rowling, J K', 'fiction', 'novel', '184', '', 201),
('Girl with the Dragon Tattoo', 'Larsson, Steig', 'fiction', 'novel', '179', '', 202),
('Girl who kicked the Hornet\'s Nest', 'Larsson, Steig', 'fiction', 'novel', '179', '', 203),
('Girl who played with Fire', 'Larsson, Steig', 'fiction', 'novel', '179', '', 204),
('Batman Handbook', '', 'fiction', 'comic', '270', '', 205),
('Murphy\'s Law', '', 'philosophy', 'psychology', '178', '', 206),
('Structure and Randomness', 'Tao, Terence', 'science', 'mathematics', '252', '', 207),
('Image Processing with MATLAB', 'Eddins, Steve', 'tech', 'signal_processing', '241', '', 208),
('Animal Farm', 'Orwell, George', 'fiction', 'classic', '180', '', 209),
('Idiot, The', 'Dostoevsky, Fyodor', 'fiction', 'classic', '197', '', 210),
('Christmas Carol, A', 'Dickens, Charles', 'fiction', 'classic', '196', '', 211);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `books`
--
ALTER TABLE `books`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `books`
--
ALTER TABLE `books`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=212;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
