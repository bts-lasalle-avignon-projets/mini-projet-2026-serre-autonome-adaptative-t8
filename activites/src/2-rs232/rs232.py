import serial

PORT = '/dev/ttyUSB0'  # Remplacer par le port série approprié
DEBIT = 9600  # Remplacer par le debit approprié

try:
    # Ouvrir le port série
    port_serie = serial.Serial(PORT, DEBIT, timeout=1)
    print(f"Port '{PORT}' ouvert")
    # Envoyer des données
    message_envoye = "Hello Serial World!\r\n"
    print(f"Envoi : '{message_envoye.strip()}'")
    port_serie.write(message_envoye.encode('ascii'))
    # Lire des données
    reponse = port_serie.readline()
    message_recu = reponse.decode('ascii', errors='ignore').strip()
    print(f"Réception : {len(message_recu)} octet(s)")
    if len(message_recu) > 0:
        print(f"Réception : '{message_recu}'")
except serial.SerialException as e:
    print(f"Erreur : {e}")
except PermissionError:
    print("Accès refusé !")
except FileNotFoundError:
    print("Port non trouvé !")
finally:
    if 'port_serie' in locals() and port_serie.is_open:
        # Fermer le port
        port_serie.close()
        print(f"Port '{PORT}' fermé")