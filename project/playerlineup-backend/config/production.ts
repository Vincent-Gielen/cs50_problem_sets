export default {
  cors: {
    origins: ['https://frontendweb-2425-vincentgielen0-1.onrender.com'],
  },
  auth: {
    jwt: {
      expirationInterval: 7 * 24 * 60 * 60, //7days in seconds
    },
  },
};
