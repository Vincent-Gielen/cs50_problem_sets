export default {
  port: 9000,
  log: {
    level: 'silly',
    disabled: false,
  },
  cors: {
    origins: ['http://localhost:5173'],
    maxAge: 3 * 60 * 60, //3u in seconden
  },
  auth: {
    maxDelay: 5000,
    jwt: {
      audience: 'playerlineup.hogent.be',
      issuer: 'playerlineup.hogent.be',
      expirationInterval: 60 * 60, //1u in seconds
      secret: 'eenveeltemoeilijksdecretdantniemadnooitzalrdadenofverkvfehrdtypen',
    },
    argon: {
      hashLength: 32,
      timeCost: 6,
      memoryCost: 2 ** 17,
    },
  },
};
