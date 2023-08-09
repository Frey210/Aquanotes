-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Waktu pembuatan: 09 Agu 2023 pada 08.34
-- Versi server: 10.4.22-MariaDB
-- Versi PHP: 8.1.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `u0173409_kedaireka`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_1`
--

CREATE TABLE `device_1` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_2`
--

CREATE TABLE `device_2` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_3`
--

CREATE TABLE `device_3` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_4`
--

CREATE TABLE `device_4` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_5`
--

CREATE TABLE `device_5` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_6`
--

CREATE TABLE `device_6` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_7`
--

CREATE TABLE `device_7` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Struktur dari tabel `device_8`
--

CREATE TABLE `device_8` (
  `id` bigint(20) NOT NULL,
  `waktu` time NOT NULL DEFAULT current_timestamp(),
  `date` date NOT NULL DEFAULT current_timestamp(),
  `water_temperature` float DEFAULT NULL,
  `do` float DEFAULT NULL,
  `tds` float DEFAULT NULL,
  `air_temperature` float DEFAULT NULL,
  `ph` float DEFAULT NULL,
  `amonia` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `device_1`
--
ALTER TABLE `device_1`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `device_2`
--
ALTER TABLE `device_2`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `device_3`
--
ALTER TABLE `device_3`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `device_4`
--
ALTER TABLE `device_4`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `device_5`
--
ALTER TABLE `device_5`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `device_6`
--
ALTER TABLE `device_6`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `device_7`
--
ALTER TABLE `device_7`
  ADD PRIMARY KEY (`id`);

--
-- Indeks untuk tabel `device_8`
--
ALTER TABLE `device_8`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `device_1`
--
ALTER TABLE `device_1`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `device_2`
--
ALTER TABLE `device_2`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `device_3`
--
ALTER TABLE `device_3`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `device_4`
--
ALTER TABLE `device_4`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `device_5`
--
ALTER TABLE `device_5`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `device_6`
--
ALTER TABLE `device_6`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `device_7`
--
ALTER TABLE `device_7`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT untuk tabel `device_8`
--
ALTER TABLE `device_8`
  MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
