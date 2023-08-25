var express = require('express');
var router = express.Router();
const Login = require("../models/mdl_user")
const Sensor_data = require("../models/mdl_Sensor_data")
const crypto = require('crypto');


function decrypt(text) {
  try {
    // Verifica si el texto es "0", si es así, lo retorna sin intentar desencriptar
    if (text === "0") {
      return text;
    }

    let textParts = text.split(':');

    if (textParts.length < 2) {
      throw new Error('Texto cifrado no tiene el formato adecuado.');
    }

    let iv = Buffer.from(textParts.shift(), 'hex');

    if (iv.length !== 16) {
      throw new Error('IV tiene un tamaño incorrecto.');
    }

    let encryptedText = Buffer.from(textParts.join(':'), 'hex');
    let decipher = crypto.createDecipheriv('aes-256-cbc', Buffer.from('utng2023utng2023utng2023utng2023'), iv);
    let decrypted = decipher.update(encryptedText);

    decrypted = Buffer.concat([decrypted, decipher.final()]);

    return decrypted.toString();

  } catch (err) {
    console.error('Error durante el descifrado:', err.message);
    return text; // Si hay un error en la desencriptación, retorna el texto original
  }
}

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('login', { title: 'Express' });
});

/* GET home page. */
router.get('/prueba', function(req, res, next) {
  res.render('pruebaBuzzer');
});


/* GET home page. */
router.get('/home', function(req, res, next) {
  res.render("index");
});


router.post("/login", async (req, res, next)=>{
  const { email, password } = req.body;

  const user = await Login.findOne({ sCorreo: email });

  if (user && user.sPass === password) {
      res.redirect("/home")
  } else {
      res.send('Correo o contraseña incorrectos');
  }
})

/* GET home page. */
router.get('/verHistorial', async function(req, res, next) {
  try {
    const documents = await Sensor_data.find({ "iActivo": { $in: ["0", "2"] } });
    console.log(documents);

    // Desencripta los datos antes de enviarlos
    const decryptedDocuments = documents.map(doc => {
      const decryptedDoc = doc.toObject(); // Convertir el documento a un objeto JavaScript para poder modificarlo
      decryptedDoc.sLatitud = decrypt(decryptedDoc.sLatitud);
      decryptedDoc.sLontitud = decrypt(decryptedDoc.sLontitud);
      return decryptedDoc;
    });


    res.render('Historial', { historial: decryptedDocuments });
  } catch (err) {
    console.error('Error al buscar los documentos:', err);
    res.status(500).send('Error interno del servidor');
  }
});




module.exports = router;
