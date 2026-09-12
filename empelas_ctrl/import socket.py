import socket
import time
import random
import json

HOST = '0.0.0.0'  # Escuta em todos os IPs
PORT = 2025       # Porta do seu C

def iniciar_simulador():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # Permite reiniciar o script sem erro de porta presa
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen()
        
        print(f"🚀 Simulador JSON rodando na porta {PORT}...")
        print("Aguardando conexao do servidor IEC 61850 em C...\n")

        while True:
            conn, addr = s.accept()
            print(f"✅ Conectado com sucesso por: {addr}")
            
            try:
                while True:
                    # Gerando dados dinâmicos realistas
                    tensao = round(random.uniform(46.5, 48.2), 6)
                    corrente = round(random.uniform(-2.5, 12.0), 6)
                    soc = round(random.uniform(80.0, 93.5), 2)
                    
                    # Simulando GPS variando levemente em Niterói
                    lat = round(random.uniform(-22.900000, -22.910000), 6)
                    lon = round(random.uniform(-43.120000, -43.130000), 6)
                    
                    timestamp = int(time.time())

                    # Estrutura JSON exata que você pediu
                    payload = {
                        "timestamp": timestamp,
                        "measurements": [
                            {
                                "id": "Corrente_Bateria_Principal",
                                "pin": 0,
                                "adc": random.randint(12000, 14000),
                                "value": corrente,
                                "unit": "A"
                            },
                            {
                                "id": "Tensao_Bateria_Principal",
                                "pin": 2,
                                "adc": random.randint(16000, 18000),
                                "value": tensao,
                                "unit": "V"
                            }
                        ],
                        "gps": {
                            "lat": lat,
                            "lon": lon
                        },
                        "battery": {
                            "enabled": True,
                            "soc_percent": soc
                        }
                    }

                    # separators=(',', ':') remove espaços para o strstr do C achar fácil
                    mensagem = json.dumps(payload, separators=(',', ':')) + "\n"
                    
                    conn.sendall(mensagem.encode('utf-8'))
                    print(f"Enviado -> V: {tensao:.2f}V | I: {corrente:.2f}A | SoC: {soc}% | GPS: {lat}, {lon}")
                    
                    time.sleep(2) # Envia a cada 2 segundos
                    
            except (ConnectionResetError, BrokenPipeError):
                print("\n⚠️ Cliente desconectou. Aguardando nova conexao...\n")

if __name__ == "__main__":
    iniciar_simulador()