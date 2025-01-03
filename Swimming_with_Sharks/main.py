import pyshark

file = "alex.pcap"
cap = pyshark.FileCapture(file)

def analyze_packets(capture):
    leaks = []
    for packet in capture:
        try:
            if 'HTTP' in packet:
                if hasattr(packet.http, 'host') and hasattr(packet.http, 'request_uri'):
                    http_info = f"HTTP Request: Host: {packet.http.host}, URI: {packet.http.request_uri}"
                    leaks.append(http_info)
                if hasattr(packet.http, 'authorization'):
                    http_auth = f"HTTP Authorization: {packet.http.authorization}"
                    leaks.append(http_auth)
            if 'FTP' in packet:
                if hasattr(packet.ftp, 'request_command') and hasattr(packet.ftp, 'request_arg'):
                    ftp_info = f"FTP Command: {packet.ftp.request_command} {packet.ftp.request_arg}"
                    leaks.append(ftp_info)
                if hasattr(packet.ftp, 'username') and hasattr(packet.ftp, 'password'):
                    ftp_credentials = f"FTP Credentials: Username: {packet.ftp.username}, Password: {packet.ftp.password}"
                    leaks.append(ftp_credentials)
            if 'SMTP' in packet:
                if hasattr(packet.smtp, 'mail_from') and hasattr(packet.smtp, 'rcpt_to'):
                    smtp_info = f"SMTP Mail From: {packet.smtp.mail_from}, Recipient: {packet.smtp.rcpt_to}"
                    leaks.append(smtp_info)
                if hasattr(packet.smtp, 'response'):
                    smtp_response = f"SMTP Response: {packet.smtp.response}"
                    leaks.append(smtp_response)
            if 'IMAP' in packet:
                if hasattr(packet.imap, 'response_text'):
                    imap_info = f"IMAP Response: {packet.imap.response_text}"
                    leaks.append(imap_info)
            if 'POP' in packet:
                if hasattr(packet.pop, 'response_text'):
                    pop_info = f"POP Response: {packet.pop.response_text}"
                    leaks.append(pop_info)

        except Exception as e:
            print(f"Error analyzing packet: {e}")
    
    return leaks

leaks = analyze_packets(cap)

with open("leaks_report.txt", "w", encoding="utf-8") as f:
    f.write("Potential Leaks Found:\n\n")
    for leak in leaks:
        f.write(f"{leak}\n")

print(f"Report generated with {len(leaks)} potential leaks.")

cap.close()
