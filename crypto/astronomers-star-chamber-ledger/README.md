Intercepted star-orders were signed with the Royal Astronomer's elliptic seal. The signing process leaked the lowest 9 bits of each nonce, though some recovered wax traces are damaged. Recover the private key and open the sealed dispatch.

Star-Chamber sealing rite:
- The seal follows the secp256k1 celestial curve.
- Each oath line is distilled through the SHA-256 alchemical hash.
- From every nonce charm, only the lowest 9 bits escaped into enemy notes.
- Some wax-imprint fragments are heat-damaged and may be wrong.

Recovered relics from the observatory vault:
- `starledger_signatures.json`
  - Intercepted oath records `(r_i, s_i, h_i, leak_i)`
- `starvault.enc`
  - The sealed dispatch, locked as AES-CTR ciphertext
- `starvault.iv`
  - The 16-byte counter origin used by that lock

How to forge the vault key once the royal secret is found:
- `aes_key = SHA256(str(d).encode()).digest()[:16]`
  where `d` is the Astronomer's recovered private seal key.
