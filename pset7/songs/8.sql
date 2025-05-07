SELECT songs.name
FROM songs
JOIN artists ON songs.artist_id = artists.id
WHERE songs.name LIKE '%feat.%'
