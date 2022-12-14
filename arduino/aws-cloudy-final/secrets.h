const char AWS_IOT_ENDPOINT[] = "a2p4fyajwx9lux-ats.iot.us-east-1.amazonaws.com";
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAOwdzNSm5zoPyCETE0JSxuU3OpCGMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA0MjYxNzM2
NDJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC4u/209dHF+1NbnikX
+681HWSabUOFvI6esU6I0oXeOxhp0xQjgCcUqJVgGYbIDSg/oU83Eg6lSwEyf8UV
c74Z69obOoFVIXOwMYMc4aEpnQvCVaCNaT6Il2EYikhCtlg75XKal9xL6Crh2jbw
XaoqXg3hQRk1HYT/2JApIs3Gj+nZTZnL28BV86vg+z/5fJdYoQBaygm7bqd1zNRS
MIpCXfK3gCw7ikKgOThEY94VxR+GZsqN4FO74ljj3hqD5aWrGO7Y4g4VKkXQGCMy
BkyxfWYByLqxyWUH5BkUP+iD7wIAhJoc/frBEUurQWZHCKLMKG/5LEvsTQ69j4pG
sa6JAgMBAAGjYDBeMB8GA1UdIwQYMBaAFCegGr5O/KlJ3xZeucPMYejyfkwxMB0G
A1UdDgQWBBSCWj9/Zaofv71D+LCmjGhQQdCNBjAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAmGPNqXgrexF1gQoYG7FXcaOM
3mA6+h3ESrvosdMb8WAw6LFnQ4GX1p+PSY542Gd4IO42LlE0egYiCFTksrfVUsS4
6Jpwt1iWDjMI/1WMsT54PRv+Mm8QQf/b+IqirfcqaZDbiHDbWFjg/IJq4QwO71eO
BIxpFyXrpPGwJp3Yfl2ewkKiJhLykMFk51NxVF8kQ5+EDczYmys54zICFzQFPW96
FGvsg5PYrdSvv9v/DD5w07xKRhzMImMbuyqHMQvV3hryawSNVpsbyRf+3C7BNrAd
BjV8IqA7+hX7sDvfFPTP4mjehee2TtmlQRE2its/tSO9egTo6ArsBSUiWqiVYw==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAuLv9tPXRxftTW54pF/uvNR1kmm1DhbyOnrFOiNKF3jsYadMU
I4AnFKiVYBmGyA0oP6FPNxIOpUsBMn/FFXO+GevaGzqBVSFzsDGDHOGhKZ0LwlWg
jWk+iJdhGIpIQrZYO+VympfcS+gq4do28F2qKl4N4UEZNR2E/9iQKSLNxo/p2U2Z
y9vAVfOr4Ps/+XyXWKEAWsoJu26ndczUUjCKQl3yt4AsO4pCoDk4RGPeFcUfhmbK
jeBTu+JY494ag+Wlqxju2OIOFSpF0BgjMgZMsX1mAci6scllB+QZFD/og+8CAISa
HP36wRFLq0FmRwiizChv+SxL7E0OvY+KRrGuiQIDAQABAoIBAD1pqacuDWXO7mBH
zQt/DTkQI3C/IDJmg9c3xI7xxbUiWjRcCpbetJ9GiBohglAhJ583phj9tMa4j5ZV
KZS/HJSLdr+UjIhbjZUmcJr6W1R1NAKP6sb4FOTdxladKfabneuTlKzWDVNixFa+
74Kq8LYS/HRE6vdgb+WJ/ireuh/nCVRCC59m+Rd2HJIpvMghCV5Cvrb2nWXNPQkb
j6Tn9WAKhP4YItxYJK0p0QZnNeVWFT2JmQZ2NS73LBbDGyVy2fUm3CvKRib93dOl
vTgqQ2PhIS0foU/B8CNeztoVFYb+/94COonXEt2l9QvvrZL6+56k4wSkFPRzOt8Q
Z5+5ep0CgYEA2jiYmpntCg7IGtF2yjFfkdLADtEBaTnFU7ar7Xbj33IEjnXW3dHn
rqIX4gQjGjUohh+7n/G1K49p9dZbx3HfoIrkNK+WKJt6qmm87cGQ/UntjFFFuzxH
dsZ++83+mCwYZMaRIHeQlZYxGbi4zQXTHU/v+uJOm+Ih89uIJIFd4gcCgYEA2LdJ
TvAZ7FXR+LeNZw9zVQhWySsP4yL1rm4UtUP/bivlScm57unpQT6k9amRDNzdGcOO
JhXlq7zjCsxgNwcwnwdnUcb9W/Xic7OtXgB5T3kuVdyivdp/N7avdG0pGfZscQ67
pNa/RgVrHtTJFs8P0emVstd/EZI+kjm6hSdkhu8CgYEAiUgjkNcXDUXBU0XFEmw/
MFDCLFAGMDl8zy5TOL+bmX10Kl8tvjyIIQ+uMKzjnGAmz0H1WijIDdBaG6Mv9+fG
hIv8Br0TnRY69CwzA+vLF91DSQvz71d7qdg0GJs9+GN9MSDOOfueBM0ItKLF940b
hAw+77khNOXs8CmCm1ybQE8CgYBz6Yy3QOrMopZc7mgeQIBScdRhYrvro+4+Lri6
vzTmy2mnDtN5Ovk8oXH/x4NCmvtTZWoparreIXhadTfdFuZlmMMlVUZ8IkbN1cOb
rKs1273xxMHyw+QZe4fawOwj687SpautngLOQ+Wopu0rWvK+Nq6P6n0Xe94lveTK
hWhaVwKBgA/SUClvnUwOiTavWhB9XeAfpp5P1PbcNws8867KLcuh2DDuTfnyu5de
eTo59y7q+mDELrJelbCMpXJDR7nhD+ASFCTPuK+OYXrIUbXqIte5FW3YALoF1RNI
R7lkdVP7cKaCKTM4q97bNRmjMNGuQUd+jYRGgvwRPyc3QK7GISce
-----END RSA PRIVATE KEY-----

)KEY";
