const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
  service: 'gmail',
  auth: {
    type: 'OAuth2',
    user: process.env.EMAIL_USER,
    clientId: process.env.CLIENT_ID,
    clientSecret: process.env.CLIENT_SECRET,
    refreshToken: process.env.REFRESH_TOKEN,
  },
});

// Verify the connection configuration
transporter.verify((error, success) => {
  if (error) {
    console.error('Error connecting to email server:', error);
  } else {
    console.log('Email server is ready to send messages');
  }
});

// Function to send email
const sendEmail = async (to, subject, text, html) => {
  try {
    const info = await transporter.sendMail({
      from: `"Bank-Transaction-System" <${process.env.EMAIL_USER}>`, // sender address
      to, // list of receivers
      subject, // Subject line
      text, // plain text body
      html, // html body
    });

    console.log('Message sent: %s', info.messageId);
    console.log('Preview URL: %s', nodemailer.getTestMessageUrl(info));
  } catch (error) {
    console.error('Error sending email:', error);
  }
};

async function sendRegistrationEmail(userEmail, name) {
  const subject = '🎉 Welcome to Bank Transaction System';

  const text = `Hello ${name},

Welcome to Bank Transaction System!

Your account has been successfully created. You can now securely manage your transactions.

If you have any questions, feel free to contact us.

Best regards,
Bank Team`;

  const html = `
  <div style="margin:0; padding:0; background-color:#f4f6f8; font-family:Arial, sans-serif;">
    <table align="center" width="100%" cellpadding="0" cellspacing="0" style="max-width:600px; margin:auto; background:#ffffff; border-radius:10px; overflow:hidden;">
      
      <!-- Header -->
      <tr>
        <td style="background:linear-gradient(90deg, #4CAF50, #2E7D32); padding:20px; text-align:center; color:white;">
          <h1 style="margin:0;">Bank Transaction System</h1>
        </td>
      </tr>

      <!-- Body -->
      <tr>
        <td style="padding:30px; color:#333;">
          <h2 style="margin-top:0;">Welcome, ${name} 👋</h2>
          <p style="font-size:16px; line-height:1.6;">
            We're excited to have you on board! Your account has been successfully created.
          </p>

          <p style="font-size:16px; line-height:1.6;">
            You can now securely manage your transactions, check balances, and explore all features.
          </p>

          <!-- Button -->
          <div style="text-align:center; margin:30px 0;">
            <a href="#" style="
              background:#4CAF50;
              color:#ffffff;
              padding:12px 25px;
              text-decoration:none;
              border-radius:5px;
              font-weight:bold;
              display:inline-block;
            ">
              Get Started
            </a>
          </div>

          <p style="font-size:14px; color:#777;">
            If you did not create this account, please contact support immediately.
          </p>
        </td>
      </tr>

      <!-- Footer -->
      <tr>
        <td style="background:#f1f1f1; padding:15px; text-align:center; font-size:12px; color:#777;">
          © ${new Date().getFullYear()} Bank Transaction System. All rights reserved.
        </td>
      </tr>

    </table>
  </div>
  `;

  return sendEmail({
    to: userEmail,
    subject,
    text,
    html,
  });
}


module.exports = {sendRegistrationEmail};